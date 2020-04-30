#include "stdafx.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "xmlictxt.h"
#include "SdXMLBodyContext_Impl.h"


SdXMLBodyContext_Impl::SdXMLBodyContext_Impl(SvXMLImport& rImport, 
	sal_uInt16 nPrfx,
	const wstring& rLName,
	const AttributeList& rAttrList)
	: SvXMLImportContext(rImport, nPrfx, rLName)
{
}


SdXMLBodyContext_Impl::~SdXMLBodyContext_Impl()
{
}

std::shared_ptr<SvXMLImportContext> SdXMLBodyContext_Impl::CreateChildContext(sal_uInt16 nPrefix, 
	const wstring& rLocalName, 
	const AttributeList& rAttributeList)
{
	return nullptr;
}
