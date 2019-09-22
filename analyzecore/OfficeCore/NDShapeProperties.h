#pragma once

#include "NDGen.h"

// p:cNvPr
struct NDNVCanvasProperties
{
	signed long spId;
	wstring strName;
};

// p:cNvGrpSpPr
struct NDNVCanvasGrpShapeProperties
{

};

// p:cNvSpPr
struct NDNVCanvasShapeProperties
{

};

// p:ph
struct NDPH
{
	wstring strType;
};

// p:nvPr
struct NDNVProperties
{
	shared_ptr<NDPH> spPh = nullptr;
};


// p:nvGrpSpPr
struct NDNVGrpShapeProperties
{
	shared_ptr<NDNVCanvasProperties> spCNvPr = nullptr;
	shared_ptr<NDNVCanvasGrpShapeProperties> spCNvGrpSpPr = nullptr;
	shared_ptr<NDNVProperties> spNvPr = nullptr;
};

//////////////////////////////////////////////////////////////////////////

// a:xfrm
struct NDXfrm
{
	Point ptOff;
	Size sizeExt;
	Point ptChOff;
	Size sizeChExt;
};

// p:grpSpPr
struct NDGrpShapeProperties
{
	shared_ptr<NDXfrm> spXfrm = nullptr;
};

//////////////////////////////////////////////////////////////////////////

// p:nvSpPr
struct NDNVShapeProperties
{
	shared_ptr<NDNVCanvasProperties> spCNvPr = nullptr;
	shared_ptr<NDNVCanvasGrpShapeProperties> spCNvGrpSpPr = nullptr;
	shared_ptr<NDNVProperties> spNvPr = nullptr;
};