#include "stdafx.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "xmlictxt.h"


SvXMLImportContext::SvXMLImportContext(SvXMLImport& rImport,
	const wstring& strPrefix,
	const wstring& rLName)
	: mrImport(rImport)
{
}


SvXMLImportContext::~SvXMLImportContext()
{
}

std::shared_ptr<SvXMLImportContext> SvXMLImportContext::CreateChildContext(const wstring& strPrefix,
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	return mrImport.CreateContext(strPrefix, rLocalName, rAttributeList);
}

void SvXMLImportContext::StartElement(const shared_ptr<AttributeList>& rAttributeList)
{

}

void SvXMLImportContext::EndElement()
{

}

void SvXMLImportContext::Characters()
{

}
