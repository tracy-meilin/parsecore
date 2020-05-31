#include "stdafx.h"
#include "attributelist.h"
#include "xmltoken.h"
#include "xmltkmap.h"
#include "xmlictxt.h"
#include "xmlimp.h"
#include "sdxmlimp_impl.h"
#include "NDOdfSlide.h"
#include "ximppage.h"
#include "ximpbody.h"

SdXMLDrawPageContext::SdXMLDrawPageContext(SvXMLImport& rImport, 
	const wstring& nPrfx, 
	const wstring& rLName, 
	const shared_ptr<AttributeList>& rAttrList, 
	const shared_ptr<CNDOdfSlide>& rSpSlide)
	: SdXMLGenericPageContext(rImport, nPrfx, rLName, rAttrList, rSpSlide)
{

}

SdXMLDrawPageContext::~SdXMLDrawPageContext()
{

}

std::shared_ptr<SvXMLImportContext> SdXMLDrawPageContext::CreateChildContext(const wstring& strPrefix,
	const wstring& rLocalName,
	const shared_ptr<AttributeList>& rAttributeList)
{
	shared_ptr<SvXMLImportContext> spContext = nullptr;

	if (spContext == nullptr)
		spContext = SdXMLGenericPageContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);

	return spContext;
}

void SdXMLDrawPageContext::EndElement()
{

}

//////////////////////////////////////////////////////////////////////////

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
		shared_ptr<CNDOdfSlide> spSlide = make_shared<CNDOdfSlide>();
		spContext = make_shared<SdXMLDrawPageContext>(GetImport(), strPrefix, rLocalName, rAttributeList, spSlide);
	}

	if (!spContext)
		spContext = SvXMLImportContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);

	return spContext;
}


