#pragma once

class SdXMLGenericPageContext 
	: public SvXMLImportContext
{
public:
	SdXMLGenericPageContext(SvXMLImport& rImport,
		const wstring& nPrfx,
		const wstring& rLName,
		const shared_ptr<AttributeList>& rAttrList, 
		const shared_ptr<CNDOdfSlide>& rSpSlide);
	~SdXMLGenericPageContext();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName,
		const shared_ptr<AttributeList>& rAttributeList) override;

private:
	shared_ptr<CNDOdfSlide> mspSlide = nullptr;
};

