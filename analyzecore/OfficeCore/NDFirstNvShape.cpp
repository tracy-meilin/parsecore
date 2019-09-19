#include "stdafx.h"
#include "NDShape.h"
#include "NDFirstNvShape.h"


CNDFirstNvShape::CNDFirstNvShape(shared_ptr<ShapeContainer>& spShapeContainer)
	: CNDShape(spShapeContainer)
{
}


CNDFirstNvShape::~CNDFirstNvShape()
{
}

NDShapeType CNDFirstNvShape::GetShapeType()
{
	return NDShapeType::FirstNvShape;
}
