#pragma once

// p:cNvPr
struct NDNVCanvasProperties
{

};

// p:cNvGrpSpPr
struct NDNVCanvasGrpShapeProperties
{

};

// p:nvPr
struct NDNVProperties
{

};

// p:nvGrpSpPr
struct NDNVGrpShapeProperties
{
	shared_ptr<NDNVCanvasProperties> spCNvPr = nullptr;
	shared_ptr<NDNVCanvasGrpShapeProperties> spCNvGrpSpPr = nullptr;
	shared_ptr<NDNVProperties> spNvPr = nullptr;
};

