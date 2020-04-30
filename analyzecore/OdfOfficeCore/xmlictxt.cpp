#include "stdafx.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "xmlictxt.h"


SvXMLImportContext::SvXMLImportContext(SvXMLImport& rImport,
	sal_uInt16 nPrfx,
	const wstring& rLName)
	: mrImport(rImport)
{
}


SvXMLImportContext::~SvXMLImportContext()
{
}

std::shared_ptr<SvXMLImportContext> SvXMLImportContext::CreateChildContext(sal_uInt16 nPrefix,
	const wstring& rLocalName, 
	const AttributeList& rAttributeList)
{
	return mrImport.CreateContext(nPrefix, rLocalName, rAttributeList);
}

void SvXMLImportContext::StartElement()
{

}

void SvXMLImportContext::EndElement()
{

}

void SvXMLImportContext::Characters()
{

}
