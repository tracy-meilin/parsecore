#pragma once

enum class NDShapeType
{
	InvalidShape = 0,
	HeaderGroupShape = 1,
};

class OfficeCore_API CNDShape
{
public:
	CNDShape(shared_ptr<ShapeContainer>& spShapeContainer);
	~CNDShape();

	virtual NDShapeType GetShapeType();

	virtual shared_ptr<NDNVGrpShapeProperties> GetNvGrpSpPr();

	virtual shared_ptr<NDNVShapeProperties> GetNvSpPr();

protected:
	shared_ptr<ShapeContainer> m_spShapeContainer = nullptr;

	//  Ù–‘
	shared_ptr<NDNVGrpShapeProperties> m_spNvGrpSpPr = nullptr;
	shared_ptr<NDGrpShapeProperties> m_spGrpSpPr = nullptr;
	shared_ptr<NDNVShapeProperties> m_spNvSpPr = nullptr;
};

