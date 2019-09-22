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
	if (m_spShapeContainer == nullptr
		|| m_spNvSpPr != nullptr)
		return m_spNvSpPr;

	shared_ptr<Shape> spShape = m_spShapeContainer->FirstChildWithType<Shape>();
	if (spShape == nullptr)
		return m_spNvSpPr;

	m_spNvSpPr = make_shared<NDNVShapeProperties>();
	m_spNvSpPr->spCNvPr = make_shared<NDNVCanvasProperties>();
	m_spNvSpPr->spCNvPr->spId = spShape->spid;
	m_spNvSpPr->spCNvPr->strName = _T("");

	shared_ptr<ClientData> spClientData = m_spShapeContainer->FirstChildWithType<ClientData>();

	return m_spNvSpPr;
}
