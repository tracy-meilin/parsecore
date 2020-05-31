#include "stdafx.h"
#include "attributelist.h"
#include "xmltoken.h"
#include "xmltkmap.h"
#include "xmlictxt.h"
#include "xmlimp.h"
#include "sdxmlimp_impl.h"
#include "ximpbody.h"


SdXMLBodyContext::SdXMLBodyContext(SdXMLImport& rImport, const wstring& strPrefix, const wstring& rLocalName)
	: SvXMLImportContext(rImport, strPrefix, rLocalName)
{
}


SdXMLBodyContext::~SdXMLBodyContext()
{
}

std::shared_ptr<SvXMLImportContext> SdXMLBodyContext::CreateChildContext(const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	shared_ptr<SvXMLImportContext> spContext = nullptr;

	if ((strPrefix == L"draw")
		&& (rLocalName == L"page"))
	{

	}

	if (!spContext)
		spContext = SvXMLImportContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);

	return spContext;
}
