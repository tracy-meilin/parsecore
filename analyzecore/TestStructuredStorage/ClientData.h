#pragma once

class ClientData 
	: public Record
{
public:
	ClientData();
	ClientData(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ClientData();

public:
	unsigned char* bytes = nullptr;
};

