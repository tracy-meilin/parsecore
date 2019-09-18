#pragma once

class PptFileFormat_API GroupShapeRecord
	: public Record
{
public:
	GroupShapeRecord();
	GroupShapeRecord(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~GroupShapeRecord();

public:
	signed long left;
	signed long top;
	signed long right;
	signed long bottom;
};

