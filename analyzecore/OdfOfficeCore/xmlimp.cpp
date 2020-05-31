#include "stdafx.h"
#include "attributelist.h"
#include "xmlictxt.h"
#include "NDOdfSlide.h"
#include "shapeimport.h"
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
	return make_shared<SvXMLImportContext>(*this, strPrefix, rLocalName);
}

std::shared_ptr<XMLShapeImportHelper> SvXMLImport::GetShapeImport()
{
	if (mShapeImport == nullptr)
		mShapeImport = make_shared<XMLShapeImportHelper>(*this);

	return mShapeImport;
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

		mpContexts.push_back(spContext);
	}
}

void SvXMLImport::endElement(const wstring& strPrefix, const wstring& strLocalName)
{
	int nCount = (int)mpContexts.size();
	if (nCount > 0)
	{
		shared_ptr<SvXMLImportContext> spContext = mpContexts.back();
		mpContexts.pop_back();
	}
}

void SvXMLImport::characters(const wstring& rChars)
{
	if (!mpContexts.empty())
	{
		mpContexts.back()->Characters();
	}
}
