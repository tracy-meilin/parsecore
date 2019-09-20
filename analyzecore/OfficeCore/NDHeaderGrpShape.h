#pragma once

class OfficeCore_API CNDHeaderGrpShape
	: public CNDShape
{
public:
	CNDHeaderGrpShape(shared_ptr<ShapeContainer>& spShapeContainer);
	~CNDHeaderGrpShape();

	virtual NDShapeType GetShapeType() override;

	virtual shared_ptr<NDNVGrpShapeProperties> GetNvGrpSpPr() override;
};

