#pragma once
class SdXMLBodyContext_Impl 
	: public SvXMLImportContext
{
public:
	SdXMLBodyContext_Impl(SvXMLImport& rImport, 
		sal_uInt16 nPrfx,
		const wstring& rLName,
		const AttributeList& rAttrList);
	virtual ~SdXMLBodyContext_Impl();

	virtual shared_ptr<SvXMLImportContext> CreateChildContext(sal_uInt16 nPrefix,
		const wstring& rLocalName, 
		const AttributeList& rAttributeList) override;
};

