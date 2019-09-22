#include "stdafx.h"
#include "NDShapeProperties.h"
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

std::shared_ptr<NDNVGrpShapeProperties> CNDShape::GetNvGrpSpPr()
{
	return m_spNvGrpSpPr;
}

std::shared_ptr<NDNVShapeProperties> CNDShape::GetNvSpPr()
{
	return m_spNvSpPr;
}
