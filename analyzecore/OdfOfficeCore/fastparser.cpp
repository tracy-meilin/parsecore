#include "stdafx.h"
#include "OdfOfficeCore.h"
#include "DebugPrintf.h"
#include "xmltoken.h"
#include "xmltkmap.h"
#include "attributelist.h"
#include "NDOdfPowerPointDoc.h"
#include "xmlimp.h"
#include "sdxmlimp_impl.h"
#include "fastparser.h"


extern "C" {

	static void call_callbackStartElement(void *userData, const xmlChar *localName, const xmlChar* prefix, const xmlChar* URI,
		int numNamespaces, const xmlChar** namespaces, int numAttributes, int defaultedAttributes, const xmlChar **attributes)
	{
		FastSaxParserImpl* pFastParser = static_cast<FastSaxParserImpl*>(userData);
		pFastParser->callbackStartElement(localName, prefix, URI, numNamespaces, namespaces, numAttributes, defaultedAttributes, attributes);
	}

	static void call_callbackEndElement(void *userData, const xmlChar* localName, const xmlChar* prefix, const xmlChar* URI)
	{
		FastSaxParserImpl* pFastParser = static_cast<FastSaxParserImpl*>(userData);
		pFastParser->callbackEndElement(localName, prefix, URI);
	}

	static void call_callbackCharacters(void *userData, const xmlChar *s, int nLen)
	{
		FastSaxParserImpl* pFastParser = static_cast<FastSaxParserImpl*>(userData);
		pFastParser->callbackCharacters(s, nLen);
	}
}

//////////////////////////////////////////////////////////////////////////

//Entity::Entity()
//	: mpParser(nullptr)
//	, mpfd(nullptr)
//	, mspOdfPowerPointDoc(nullptr)
//{
//
//}
//
//
//void Entity::startElement(const wstring& strPrefix, const wstring& strLocalName)
//{
//
//}
//
//void Entity::characters(const wstring& strChars)
//{
//
//}
//
//void Entity::endElement()
//{
//
//}

//////////////////////////////////////////////////////////////////////////

FastSaxParserImpl::FastSaxParserImpl(FastSaxParser*)
{
	m_spSvxXMLImport = make_shared<SdXMLImport>();
	m_spAttributeList = make_shared<AttributeList>();
	m_spOdfPowerPointDoc = make_shared<CNDOdfPowerPointDoc>();
}

shared_ptr<CNDOdfPowerPointDoc> FastSaxParserImpl::parseFodp(const wstring& strFodpPath)
{
	xmlInitParser();
	
	parse(strFodpPath);

	return m_spOdfPowerPointDoc;
}

void FastSaxParserImpl::parse(const wstring& strFodpPath)
{
	const int BUFFER_SIZE = 16 * 1024;
	char chars[BUFFER_SIZE];

	static xmlSAXHandler callbacks;
	callbacks.startElementNs = call_callbackStartElement;
	callbacks.endElementNs = call_callbackEndElement;
	callbacks.characters = call_callbackCharacters;
	callbacks.initialized = XML_SAX2_MAGIC;

	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	FILE *fd = fopen(converterX.to_bytes(strFodpPath).c_str(), "rb");
	if (fd == nullptr)
		return;

	int nRead = 0;
	do
	{
		nRead = fread(chars, 1, sizeof(chars) - 1, fd);

		bool bContinue = true;
		if (mpParser == nullptr)
		{
			// create parser with proper encoding (needs the first chunk of data)
			mpParser = xmlCreatePushParserCtxt(&callbacks, this,
				chars, nRead, nullptr);

			// Tell libxml2 parser to decode entities in attribute values.
			xmlCtxtUseOptions(mpParser, XML_PARSE_NOENT);
		}
		else
		{
			bContinue = xmlParseChunk(mpParser, chars, nRead, 0)
				== XML_ERR_OK;
		}
		
	} while (nRead > 0);
}

void FastSaxParserImpl::callbackStartElement(const xmlChar *localName, 
	const xmlChar* prefix, 
	const xmlChar* URI, 
	int numNamespaces, 
	const xmlChar** namespaces, 
	int numAttributes, 
	int defaultedAttributes, 
	const xmlChar **attributes)
{
	if (m_spAttributeList)
		m_spAttributeList->Clear();

	static std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;

	wstring strPrefix = strCnv.from_bytes(XML_CAST(prefix));
	wstring strLocalName = strCnv.from_bytes(XML_CAST(localName));
	
	for (int i = 0; i < numAttributes * 5; i += 5)
	{
		string strName, strValue;
		// attributes[] is ( localname / prefix / nsURI / valueBegin / valueEnd )
		if (attributes[i + 1] != nullptr)
		{
			string strAttrPrefix = string(XML_CAST(attributes[i + 1]));
			strName = strAttrPrefix + ":" + string(XML_CAST(attributes[i]));
			strValue = string(XML_CAST(attributes[i + 3]), attributes[i + 4] - attributes[i + 3]);
		}
		else
		{
			strName = string(XML_CAST(attributes[i]));
			strValue = string(XML_CAST(attributes[i + 3]), attributes[i + 4] - attributes[i + 3]);
		}

		wstring strNameUnicode = strCnv.from_bytes(strName);
		wstring strValueUnicode = strCnv.from_bytes(strValue);

		m_spAttributeList->AddAttribute(strNameUnicode, L"", strValueUnicode);

		REPORT_DEBUG(L"attribute_name: %s, attribute_value: %s \n", strNameUnicode.c_str(), strValueUnicode.c_str());
	}

	if (m_spSvxXMLImport)
	{
		m_spSvxXMLImport->startElement(strPrefix, strLocalName, m_spAttributeList);
	}

	//rEntity.startElement();
}

void FastSaxParserImpl::callbackEndElement(const xmlChar* localName, const xmlChar* prefix, const xmlChar* URI)
{
	if (!mStrPendingCharacters.empty())
		sendPendingCharacters();

	static std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;

	wstring strPrefix = strCnv.from_bytes(XML_CAST(prefix));
	wstring strLocalName = strCnv.from_bytes(XML_CAST(localName));

	if (m_spSvxXMLImport)
	{
		m_spSvxXMLImport->endElement(strPrefix, strLocalName);
	}

	/*Entity& rEntity = getEntity();
	rEntity.endElement();*/
}

void FastSaxParserImpl::callbackCharacters(const xmlChar* s, int nLen)
{
	string strTmp = string(XML_CAST(s), nLen);
	std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
	
	mStrPendingCharacters += strCnv.from_bytes(strTmp);

	//REPORT_DEBUG(L"characters: %s \n", strCharacters.c_str());
}
//
//void FastSaxParserImpl::pushEntity(const Entity& rEntity)
//{
//	maEntities.push(rEntity);
//	mpTop = &maEntities.top();
//}
//
//void FastSaxParserImpl::popEntity()
//{
//	maEntities.pop();
//	mpTop = !maEntities.empty() ? &maEntities.top() : nullptr;
//}

void FastSaxParserImpl::sendPendingCharacters()
{
	//Entity& rEntity = getEntity();
	
	//rEntity.characters(mStrPendingCharacters);

	REPORT_DEBUG(L"characters: %s \n", mStrPendingCharacters.c_str());

	if (m_spSvxXMLImport)
	{
		m_spSvxXMLImport->characters(mStrPendingCharacters);
	}

	mStrPendingCharacters.clear();
}

//////////////////////////////////////////////////////////////////////////


FastSaxParser::FastSaxParser()
	: mpImpl(new FastSaxParserImpl(this))
{
	//mpImpl->mspAttributeList = make_shared<AttributeList>();
}


FastSaxParser::~FastSaxParser()
{
}

shared_ptr<CNDOdfPowerPointDoc> FastSaxParser::parseFodp(const wstring& strFodpPath)
{
	if (mpImpl == nullptr)
		return nullptr;

	return mpImpl->parseFodp(strFodpPath);
}
