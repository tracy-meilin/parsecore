#pragma once

class OfficeCore_API CNDFirstNvShape 
	: public CNDShape
{
public:
	CNDFirstNvShape(shared_ptr<ShapeContainer>& spShapeContainer);
	~CNDFirstNvShape();

	virtual NDShapeType GetShapeType() override;
};

