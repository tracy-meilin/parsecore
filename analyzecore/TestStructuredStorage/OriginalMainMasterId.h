#pragma once

class OriginalMainMasterId 
	: public Record
{
public:
	OriginalMainMasterId();
	OriginalMainMasterId(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~OriginalMainMasterId();

public:
	unsigned long MainMasterId;
};

