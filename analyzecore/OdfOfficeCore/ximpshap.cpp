#include "stdafx.h"
#include "Size.h"
#include "Point.h"
#include "attributelist.h"
#include "xmlictxt.h"
#include "xmlimp.h"
#include "NDOdfSlide.h"
#include "shapeimport.h"
#include "converter.h"
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
	if ((nPrfx == L"presentation"))
	{
		if (rLName == L"style-name")
		{
			maDrawStyleName = rValue;
		}
		else if (rLName == L"class")
		{
			maPresentationClass = rValue;
		}
		else if (rLName == L"placeholder")
		{
			mbIsPlaceholder = rValue == L"true" ? true : false;
			if (mbIsPlaceholder)
				mbClearDefaultAttributs = false;
		}
	}
	else if ((nPrfx == L"xml"))
	{
		if (rLName == L"id")
		{
			maShapeId = rValue;
			mbHaveXmlId = true;
		}
	}
	else if (nPrfx == L"draw")
	{
		if (rLName == L"id")
		{
			if (!mbHaveXmlId){ maShapeId = rValue; }
		}
		else if (rLName == L"layer")
		{
			maLayerName = rValue;
		}
	}
	else if (nPrfx == L"svg")
	{
		if (rLName == L"x")
		{
			sax::converter::convertMeasure(maPosition.X, rValue);
		}
		else if (rLName == L"y")
		{
			sax::converter::convertMeasure(maPosition.Y, rValue);
		}
		else if (rLName == L"width")
		{
			sax::converter::convertMeasure(maSize.Width, rValue);
		}
		else if (rLName == L"height")
		{
			sax::converter::convertMeasure(maSize.Height, rValue);
		}
	}
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

	if (mspImplContext == nullptr)
	{
		spContext = GetImport().GetShapeImport()->CreateFrameChildContext(GetImport(), strPrefix, rLocalName, rAttributeList, mspSlide, mspAttributeList);
	}

	if (spContext)
		spContext = SvXMLImportContext::CreateChildContext(strPrefix, rLocalName, rAttributeList);

	return spContext;
}


//////////////////////////////////////////////////////////////////////////


SdXMLTextBoxShapeContext::SdXMLTextBoxShapeContext(SvXMLImport& rImport, 
	const wstring& nPrfx, 
	const wstring& rLName, 
	const shared_ptr<AttributeList>& rAttributeList, 
	const shared_ptr<CNDOdfSlide>& rSpSlide)
	: SdXMLShapeContext(rImport, nPrfx, rLName, rAttributeList, rSpSlide)
{

}

void SdXMLTextBoxShapeContext::StartElement(const shared_ptr<AttributeList>& rAttributeList)
{

}

void SdXMLTextBoxShapeContext::processAttribute(const wstring& nPrfx, const wstring& rLName, const wstring& rValue)
{
	SdXMLShapeContext::processAttribute(nPrfx, rLName, rValue);
}

SdXMLTextBoxShapeContext ::~SdXMLTextBoxShapeContext()
{
}