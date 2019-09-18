#pragma once

class PptFileFormat_API ProgBinaryTagDataBlob
	: public RegularContainer
{
public:
	ProgBinaryTagDataBlob();
	ProgBinaryTagDataBlob(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ProgBinaryTagDataBlob();
};

