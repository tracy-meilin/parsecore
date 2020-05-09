#include "stdafx.h"
#include "attributelist.h"
#include "xmlictxt.h"
#include "xmlimp.h"


SvXMLImport::SvXMLImport()
{
}


SvXMLImport::~SvXMLImport()
{
}

std::shared_ptr<SvXMLImportContext> SvXMLImport::CreateContext(const wstring& strPrefix,
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttrList)
{
	//return make_shared<SvXMLImportContext>(*this, strPrefix, rLocalName);
	if ((strPrefix == L"office")
		&& (rLocalName == L"document"))
	{

	}

	return nullptr;
}

void SvXMLImport::startElement(const wstring& strPrefix, 
	const wstring& strLocalName, 
	const shared_ptr<AttributeList>& spAttributeList)
{
	shared_ptr<SvXMLImportContext> spContext;
	int nCount = (int)mpContexts.size();
	if (nCount > 0)
	{
		spContext = mpContexts[nCount - 1]->CreateChildContext(strPrefix, strLocalName, spAttributeList);
	}
	else
	{
		spContext = CreateContext(strPrefix, strLocalName, spAttributeList);
	}

	if (spContext)
	{
		spContext->StartElement(spAttributeList);
	}
}
