#pragma once

enum class NDShapeType
{
	InvalidShape = 0,
	FirstNvShape = 1,
};

class OfficeCore_API CNDShape
{
public:
	CNDShape(shared_ptr<ShapeContainer>& spShapeContainer);
	~CNDShape();

	virtual NDShapeType GetShapeType();

protected:
	shared_ptr<ShapeContainer> m_spShapeContainer = nullptr;
};

