#include "stdafx.h"
#include "attributelist.h"
#include "xmlimp.h"
#include "xmlictxt.h"
#include "NDOdfSlide.h"

#include "shapeimport.h"
#include "ximpshap.h"





XMLShapeImportHelper::XMLShapeImportHelper(SvXMLImport& rImporter)
{

}

XMLShapeImportHelper::~XMLShapeImportHelper()
{
}

SvXMLShapeContext::SvXMLShapeContext(SvXMLImport& rImport, 
	const wstring& nPrfx, 
	const wstring& rLName)
	: SvXMLImportContext(rImport, nPrfx, rLName)
{

}


std::shared_ptr<SvXMLShapeContext> XMLShapeImportHelper::CreateGroupChildContext(SvXMLImport& rImport, 
	const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList, 
	const shared_ptr<CNDOdfSlide>& rSpSlide)
{
	shared_ptr<SdXMLShapeContext> spContext = nullptr;
	int nAttrCount = rAttributeList ? rAttributeList->getLength() : 0;

	if ((strPrefix == L"draw")
		&& (rLocalName == L"frame"))
	{
		spContext = make_shared<SdXMLFrameShapeContext>(rImport, strPrefix, rLocalName, rAttributeList, rSpSlide);
	}
	else
	{
		spContext = make_shared<SdXMLShapeContext>(rImport, strPrefix, rLocalName, rAttributeList, rSpSlide);
	}

	for (int i = 0; i < nAttrCount; ++i)
	{
		const wstring& rAttrName = rAttributeList->getNameByIndex(i);
		const wstring& rValue = rAttributeList->getValueByIndex(i);

		if (spContext)
			spContext->processAttribute(strPrefix, rAttrName, rValue);
	}

	return spContext;
}

