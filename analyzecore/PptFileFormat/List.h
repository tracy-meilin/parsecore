#pragma once

class PptFileFormat_API List
	: public RegularContainer
{
public:
	List();
	List(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~List();
};

