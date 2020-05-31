#pragma once

// draw:page
class SdXMLGenericPageContext;
class SdXMLDrawPageContext 
	: public SdXMLGenericPageContext
{
public:
	SdXMLDrawPageContext(SvXMLImport& rImport,
		const wstring& nPrfx,
		const wstring& rLName,
		const shared_ptr<AttributeList>& rAttrList,
		const shared_ptr<CNDOdfSlide>& rSpSlide);
	virtual ~SdXMLDrawPageContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttributeList) override;

	virtual void EndElement() override;
};

// office:presentation
class SdXMLBodyContext 
	: public SvXMLImportContext
{
	const SdXMLImport& GetSdImport() const { return static_cast<const SdXMLImport&>(GetImport()); }
	SdXMLImport& GetSdImport() { return static_cast<SdXMLImport&>(GetImport()); }

public:
	SdXMLBodyContext(SdXMLImport& rImport, const wstring& strPrefix, const wstring& rLocalName);
	virtual ~SdXMLBodyContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttributeList) override;
};

