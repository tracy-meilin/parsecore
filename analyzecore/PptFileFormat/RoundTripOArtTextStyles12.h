#pragma once

class PptFileFormat_API RoundTripOArtTextStyles12
	: public XmlContainer
{
public:
	RoundTripOArtTextStyles12();
	RoundTripOArtTextStyles12(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~RoundTripOArtTextStyles12();
};

