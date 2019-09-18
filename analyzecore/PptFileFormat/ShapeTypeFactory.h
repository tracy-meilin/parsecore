#pragma once

class ShapeTypeFactory 
	: public util::Singleton<ShapeTypeFactory>
{
public:
	ShapeTypeFactory();
	~ShapeTypeFactory();

	shared_ptr<ShapeType> CreateShapeType(unsigned long typeCode);
};

