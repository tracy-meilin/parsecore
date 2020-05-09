#pragma once

//struct Entity
//{
//	xmlParserCtxtPtr	mpParser;
//	FILE*	mpfd;
//	shared_ptr<CNDOdfPowerPointDoc> mspOdfPowerPointDoc;
//	shared_ptr<AttributeList> mspAttributeList;
//
//	Entity();
//
//	void	startElement(const wstring& strPrefix, const wstring& strLocalName);
//	void	characters(const wstring& strChars);
//	void	endElement();
//};

class FastSaxParser;
class CNDOdfPowerPointDoc;

class FastSaxParserImpl
{
public:
	explicit FastSaxParserImpl(FastSaxParser* pFront);

	shared_ptr<CNDOdfPowerPointDoc> parseFodp(const wstring& strFodpPath);

	void parse(const wstring& strFodpPath);

	// called by the C callbacks of the expat parser
	void callbackStartElement(const xmlChar *localName, const xmlChar* prefix, const xmlChar* URI,
		int numNamespaces, const xmlChar** namespaces, int numAttributes, int defaultedAttributes, const xmlChar **attributes);
	void callbackEndElement(const xmlChar* localName, const xmlChar* prefix, const xmlChar* URI);
	void callbackCharacters(const xmlChar* s, int nLen);

	/*void pushEntity(const Entity& rEntity);
	void popEntity();
	Entity& getEntity()             { return *mpTop; }*/

private:
	void sendPendingCharacters();

public:
	shared_ptr<CNDOdfPowerPointDoc> m_spOdfPowerPointDoc = nullptr;
	shared_ptr<SvXMLImport> m_spSvxXMLImport = nullptr;
	shared_ptr<AttributeList> m_spAttributeList;

private:
	//Entity* mpTop;
	//std::stack< Entity > maEntities;      /// Entity stack for each call of parseStream().
	wstring mStrPendingCharacters;
	xmlParserCtxtPtr	mpParser;
};

class FastSaxParser
{
public:
	FastSaxParser();
	~FastSaxParser();

	shared_ptr<CNDOdfPowerPointDoc> parseFodp(const wstring& strFodpPath);

private:
	std::unique_ptr<FastSaxParserImpl> mpImpl;
};

