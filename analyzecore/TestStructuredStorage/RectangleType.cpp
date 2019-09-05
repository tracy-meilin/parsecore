#include "stdafx.h"
#include "GlobalDefines.h"
#include "Handle.h"
#include "ProtectionBooleans.h"
#include "ShapeType.h"
#include "RectangleType.h"


RectangleType::RectangleType()
{
	this->ShapeConcentricFill = true;
	this->Joins = JoinStyleSpace::miter;
	this->Path = _T("m,l,21600r21600,l21600,xe");
}


RectangleType::~RectangleType()
{
}
