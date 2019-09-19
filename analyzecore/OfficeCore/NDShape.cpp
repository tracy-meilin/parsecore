#include "stdafx.h"
#include "NDShape.h"


CNDShape::CNDShape(shared_ptr<ShapeContainer>& spShapeContainer)
	: m_spShapeContainer(spShapeContainer)
{
}


CNDShape::~CNDShape()
{
}

NDShapeType CNDShape::GetShapeType()
{
	return NDShapeType::InvalidShape;
}
