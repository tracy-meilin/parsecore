#pragma once

class DrawingRecord 
	: public Record
{
public:
	DrawingRecord();
	DrawingRecord(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~DrawingRecord();

public:
	unsigned long csp;
	signed long spidCur;
};

