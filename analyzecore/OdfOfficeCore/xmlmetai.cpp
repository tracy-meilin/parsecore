#include "stdafx.h"
#include "attributelist.h"
#include "xmlictxt.h"
#include "xmlmetai.h"


XMLDocumentBuilderContext::XMLDocumentBuilderContext(SvXMLImport& rImport, 
	const wstring& strPrfx, 
	const wstring& rLName, 
	const shared_ptr<AttributeList>& rAttrList)
	: SvXMLImportContext(rImport, strPrfx, rLName)
{

}



XMLDocumentBuilderContext::~XMLDocumentBuilderContext()
{

}

std::shared_ptr<SvXMLImportContext> XMLDocumentBuilderContext::CreateChildContext(const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	return make_shared<XMLDocumentBuilderContext>(GetImport(), strPrefix, rLocalName, rAttributeList);
}

void XMLDocumentBuilderContext::StartElement(const shared_ptr<AttributeList>& rAttributeList)
{

}

void XMLDocumentBuilderContext::EndElement()
{

}

void XMLDocumentBuilderContext::Characters()
{

}

//////////////////////////////////////////////////////////////////////////

SvXMLMetaDocumentContext::SvXMLMetaDocumentContext(SvXMLImport& rImport,
	const wstring& strPrfx,
	const wstring& rLName,
	const shared_ptr<AttributeList>& rAttrList)
	: SvXMLImportContext(rImport, strPrfx, rLName)
{
}


SvXMLMetaDocumentContext::~SvXMLMetaDocumentContext()
{
}

std::shared_ptr<SvXMLImportContext> SvXMLMetaDocumentContext::CreateChildContext(const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	if ((strPrefix == L"office")
		&& (rLocalName == L"meta"))
	{
		return make_shared<XMLDocumentBuilderContext>(GetImport(), strPrefix, rLocalName, rAttributeList);
	}
	else
	{
		return make_shared<SvXMLImportContext>(GetImport(), strPrefix, rLocalName);
	}
}
