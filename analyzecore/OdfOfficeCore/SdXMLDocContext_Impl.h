#pragma once

class SdXMLDocContext_Impl 
	: public virtual SvXMLImportContext
{
public:
	SdXMLDocContext_Impl(SvXMLImport& rImport, 
		sal_uInt16 nPrfx,
		const wstring& rLName, 
		const AttributeList& rAttrList);
	virtual ~SdXMLDocContext_Impl();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(sal_uInt16 nPrefix,
		const wstring& rLocalName, 
		const AttributeList& rAttributeList) override;

protected:
	SdXMLImport& GetSdImport(){ return static_cast<SdXMLImport&>(GetImport()); }
};

