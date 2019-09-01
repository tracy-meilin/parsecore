#pragma once

class Environment 
	: public RegularContainer
{
public:
	Environment();
	Environment(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Environment();
};

