#pragma once

class PptFileFormat_API ProgTags
	: public RegularContainer
{
public:
	ProgTags();
	ProgTags(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ProgTags();
};

