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

	virtual shared_ptr<NDShapeProperties> GetSpPr();

	virtual shared_ptr<CNDTextBody> GetTxBody();

protected:
	shared_ptr<ShapeContainer> m_spShapeContainer = nullptr;

	shared_ptr<ShapeOptions> m_spShapeOptions = nullptr;

	//  Ù–‘
	shared_ptr<NDNVGrpShapeProperties> m_spNvGrpSpPr = nullptr;

	shared_ptr<NDGrpShapeProperties> m_spGrpSpPr = nullptr;

	shared_ptr<NDNVShapeProperties> m_spNvSpPr = nullptr;

	shared_ptr<NDShapeProperties> m_spSpPr = nullptr;

	shared_ptr<CNDTextBody> m_spTxBody = nullptr;
};

