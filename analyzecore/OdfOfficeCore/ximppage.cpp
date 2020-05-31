#include "stdafx.h"

#include "attributelist.h"
#include "xmlictxt.h"
#include "xmlimp.h"
#include "NDOdfSlide.h"
#include "shapeimport.h"
#include "ximppage.h"


SdXMLGenericPageContext::SdXMLGenericPageContext(SvXMLImport& rImport, 
	const wstring& nPrfx, 
	const wstring& rLName, 
	const shared_ptr<AttributeList>& rAttrList, 
	const shared_ptr<CNDOdfSlide>& rSpSlide)
	: SvXMLImportContext(rImport, nPrfx, rLName)
	, mspSlide(rSpSlide)
{

}

SdXMLGenericPageContext::~SdXMLGenericPageContext()
{
}

std::shared_ptr<SvXMLImportContext> SdXMLGenericPageContext::CreateChildContext(const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	shared_ptr<SvXMLImportContext> spContext = nullptr;

	spContext = GetImport().GetShapeImport()->CreateGroupChildContext(GetImport(), strPrefix, rLocalName, rAttributeList, mspSlide);

	if (!spContext)
		spContext = SvXMLImportContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);

	return spContext;
}
