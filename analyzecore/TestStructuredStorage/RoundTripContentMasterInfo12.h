#pragma once

class RoundTripContentMasterInfo12 
	: public XmlContainer
{
public:
	RoundTripContentMasterInfo12();
	RoundTripContentMasterInfo12(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~RoundTripContentMasterInfo12();
};

