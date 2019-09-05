#pragma once

class DrawingContainer 
	: public RegularContainer
{
public:
	DrawingContainer();
	DrawingContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~DrawingContainer();
};

