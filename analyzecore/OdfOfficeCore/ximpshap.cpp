#include "stdafx.h"
#include "attributelist.h"
#include "xmlictxt.h"
#include "NDOdfSlide.h"
#include "shapeimport.h"
#include "ximpshap.h"


SdXMLShapeContext::SdXMLShapeContext(SvXMLImport& rImport, 
	const wstring& nPrfx, 
	const wstring& rLName, 
	const shared_ptr<AttributeList>& rAttributeList, 
	const shared_ptr<CNDOdfSlide>& rSpSlide)
	: SvXMLShapeContext(rImport, nPrfx, rLName)
	, mspAttributeList(rAttributeList)
	, mspSlide(rSpSlide)
{

}

SdXMLShapeContext::~SdXMLShapeContext()
{
}


void SdXMLShapeContext::StartElement(const shared_ptr<AttributeList>& rAttributeList)
{

}

void SdXMLShapeContext::EndElement()
{

}

void SdXMLShapeContext::processAttribute(const wstring& nPrfx, 
	const wstring& rLName, 
	const wstring& rValue)
{

}



//////////////////////////////////////////////////////////////////////////

SdXMLFrameShapeContext::SdXMLFrameShapeContext(SvXMLImport& rImport, 
	const wstring& nPrfx, 
	const wstring& rLName, 
	const shared_ptr<AttributeList>& rAttributeList, 
	const shared_ptr<CNDOdfSlide>& rSpSlide)
	: SdXMLShapeContext(rImport, nPrfx, rLName, rAttributeList, rSpSlide)
{

}

SdXMLFrameShapeContext::~SdXMLFrameShapeContext()
{

}

std::shared_ptr<SvXMLImportContext> SdXMLFrameShapeContext::CreateChildContext(const wstring& strPrefix, 
	const wstring& rLocalName, 
	const shared_ptr<AttributeList>& rAttributeList)
{
	shared_ptr<SvXMLImportContext> spContext = nullptr;

	if (spContext)
		spContext = SvXMLImportContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);

	return spContext;
}
