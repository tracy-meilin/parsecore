#include "stdafx.h"
#include "xmlnmspe.h"
#include "xmltoken.h"
#include "xmltkmap.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "xmlictxt.h"
#include "sdxmlimp_impl.h"
#include "xmlmetai.h"
#include "SdXMLBodyContext_Impl.h"
#include "SdXMLDocContext_Impl.h"
#include "sdxmlimp_impl.h"

using namespace ::xmloff::token;

SdXMLImport::SdXMLImport()
{
}


SdXMLImport::~SdXMLImport()
{
}

std::shared_ptr<SvXMLImportContext> SdXMLImport::CreateContext(const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttrList)
{
	shared_ptr<SvXMLImportContext> spContext = nullptr;
	//
	if ((strPrefix == L"office")
		&& (rLocalName == L"document"))
	{
		spContext = make_shared<SdXMLFlatDocContext_Impl>(*this, strPrefix, rLocalName, rAttrList);
	}

	return nullptr;
}

const SvXMLTokenMap& SdXMLImport::GetDocElemTokenMap()
{
	if (!mpDocElemTokenMap)
	{
		static const SvXMLTokenMapEntry aDocElemTokenMap[] =
		{
			{ XML_NAMESPACE_OFFICE, XML_FONT_FACE_DECLS, XML_TOK_DOC_FONTDECLS },
			{ XML_NAMESPACE_OFFICE, XML_STYLES, XML_TOK_DOC_STYLES },
			{ XML_NAMESPACE_OFFICE, XML_AUTOMATIC_STYLES, XML_TOK_DOC_AUTOSTYLES },
			{ XML_NAMESPACE_OFFICE, XML_MASTER_STYLES, XML_TOK_DOC_MASTERSTYLES },
			{ XML_NAMESPACE_OFFICE, XML_META, XML_TOK_DOC_META },
			{ XML_NAMESPACE_OFFICE, XML_SCRIPTS, XML_TOK_DOC_SCRIPT },
			{ XML_NAMESPACE_OFFICE, XML_BODY, XML_TOK_DOC_BODY },
			{ XML_NAMESPACE_OFFICE, XML_SETTINGS, XML_TOK_DOC_SETTINGS },
			XML_TOKEN_MAP_END
		};

		mpDocElemTokenMap = new SvXMLTokenMap(aDocElemTokenMap);
	} // if(!mpDocElemTokenMap)

	return *mpDocElemTokenMap;
}
