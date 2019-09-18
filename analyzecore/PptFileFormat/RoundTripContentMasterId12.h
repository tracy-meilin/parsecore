#pragma once

class PptFileFormat_API RoundTripContentMasterId12
	: public Record
{
public:
	RoundTripContentMasterId12();
	RoundTripContentMasterId12(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~RoundTripContentMasterId12();

public:
	unsigned long MainMasterId;
	unsigned long ContentMasterInstanceId;
};

