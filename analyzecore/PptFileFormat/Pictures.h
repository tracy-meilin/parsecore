#pragma once

class PptFileFormat_API Pictures
	: public Record
{
public:
	Pictures();
	Pictures(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~Pictures();

public:
	map<__int64, shared_ptr<Record>> _pictures;
};

