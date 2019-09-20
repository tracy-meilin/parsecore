#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDShape.h"
#include "NDHeaderGrpShape.h"


CNDHeaderGrpShape::CNDHeaderGrpShape(shared_ptr<ShapeContainer>& spShapeContainer)
	: CNDShape(spShapeContainer)
{
}


CNDHeaderGrpShape::~CNDHeaderGrpShape()
{
}

NDShapeType CNDHeaderGrpShape::GetShapeType()
{
	return NDShapeType::HeaderGroupShape;
}

std::shared_ptr<NDNVGrpShapeProperties> CNDHeaderGrpShape::GetNvGrpSpPr()
{
	if (m_spShapeContainer == nullptr
		|| m_spNvGrpSpPr != nullptr)
		return m_spNvGrpSpPr;

	// ≥ı ºªØ
	shared_ptr<GroupShapeRecord> spGroupShapeRecord = m_spShapeContainer->FirstChildWithType<GroupShapeRecord>();
	
}

