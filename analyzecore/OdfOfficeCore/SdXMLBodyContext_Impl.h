#pragma once
class SdXMLBodyContext_Impl 
	: public SvXMLImportContext
{
	SdXMLImport& GetSdImport() { return static_cast<SdXMLImport&>(GetImport()); }

public:
	SdXMLBodyContext_Impl(SvXMLImport& rImport, 
		const wstring& nPrfx,
		const wstring& rLName,
		const shared_ptr<AttributeList>& rAttrList);
	virtual ~SdXMLBodyContext_Impl();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName, 
		const shared_ptr<AttributeList>& rAttributeList) override;
};

