#pragma once

class PPDrawing 
	: public RegularContainer
{
public:
	PPDrawing();
	PPDrawing(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~PPDrawing();
};

