#pragma once

enum SdXMLDocElemTokenMap
{
	XML_TOK_DOC_FONTDECLS,
	XML_TOK_DOC_STYLES,
	XML_TOK_DOC_AUTOSTYLES,
	XML_TOK_DOC_MASTERSTYLES,
	XML_TOK_DOC_META,
	XML_TOK_DOC_BODY,
	XML_TOK_DOC_SCRIPT,
	XML_TOK_DOC_SETTINGS,
	XML_TOK_OFFICE_END = XML_TOK_UNKNOWN
};

class SdXMLImport 
	: public SvXMLImport
{
public:
	SdXMLImport();
	~SdXMLImport();

	virtual shared_ptr<SvXMLImportContext> CreateContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttrList);

	shared_ptr<SvXMLImportContext> CreateBodyContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttrList);

	const SvXMLTokenMap& GetDocElemTokenMap();

private:
	// token map lists
	SvXMLTokenMap*              mpDocElemTokenMap;
};

