#pragma once

class PptFileFormat_API ProgBinaryTag
	: public RegularContainer
{
public:
	ProgBinaryTag();
	ProgBinaryTag(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ProgBinaryTag();
};

