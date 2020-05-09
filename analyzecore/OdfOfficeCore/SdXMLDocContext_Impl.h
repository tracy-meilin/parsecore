#pragma once

class SdXMLDocContext_Impl 
	: public virtual SvXMLImportContext
{
public:
	SdXMLDocContext_Impl(SvXMLImport& rImport, 
		const wstring& strPrfx,
		const wstring& rLName, 
		const shared_ptr<AttributeList>& rAttrList);
	virtual ~SdXMLDocContext_Impl();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(const wstring& strPrefix,
		const wstring& rLocalName, 
		const shared_ptr<AttributeList>& rAttributeList) override;

protected:
	SdXMLImport& GetSdImport(){ return static_cast<SdXMLImport&>(GetImport()); }
};

