#pragma once

class PptFileFormat_API UnknownRecord
	: public Record
{
public:
	UnknownRecord();
	UnknownRecord(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~UnknownRecord();
};

