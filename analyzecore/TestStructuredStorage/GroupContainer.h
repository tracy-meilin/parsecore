#pragma once

class GroupContainer 
	: public RegularContainer
{
public:
	GroupContainer();
	GroupContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~GroupContainer();

public:
	int Index;
};

