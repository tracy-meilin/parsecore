#include "stdafx.h"
#include "attributelist.h"
#include "xmltoken.h"
#include "xmltkmap.h"
#include "xmlimp.h"
#include "xmlictxt.h"
#include "sdxmlimp_impl.h"
#include "SdXMLBodyContext_Impl.h"


SdXMLBodyContext_Impl::SdXMLBodyContext_Impl(SvXMLImport& rImport, 
	const wstring& strPrfx,
	const wstring& rLName,
	const shared_ptr<AttributeList>& rAttrList)
	: SvXMLImportContext(rImport, strPrfx, rLName)
{
}


SdXMLBodyContext_Impl::~SdXMLBodyContext_Impl()
{
}

std::shared_ptr<SvXMLImportContext> SdXMLBodyContext_Impl::CreateChildContext(const wstring& strPrefix,
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	return GetSdImport().CreateBodyContext(strPrefix, rLocalName, rAttributeList);
}
