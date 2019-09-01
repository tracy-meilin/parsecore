#pragma once
class DrawingGroup 
	: public RegularContainer
{
public:
	DrawingGroup();
	DrawingGroup(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~DrawingGroup();
};

