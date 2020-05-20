#pragma once

class XMLDocumentBuilderContext : public SvXMLImportContext
{
public:
	XMLDocumentBuilderContext(SvXMLImport& rImport,
		const wstring& strPrfx,
		const wstring& rLName,
		const shared_ptr<AttributeList>& rAttrList);

	virtual ~XMLDocumentBuilderContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttributeList) override;

	virtual void StartElement(const shared_ptr<AttributeList>& rAttributeList);

	virtual void EndElement();

	virtual void Characters();
};

class SvXMLMetaDocumentContext 
	: public virtual SvXMLImportContext
{
public:
	SvXMLMetaDocumentContext(SvXMLImport& rImport,
		const wstring& strPrfx,
		const wstring& rLName,
		const shared_ptr<AttributeList>& rAttrList);
	virtual ~SvXMLMetaDocumentContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttributeList) override;
};

