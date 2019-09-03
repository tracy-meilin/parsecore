#pragma once
class EndDocument 
	: public Record
{
public:
	EndDocument();
	EndDocument(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~EndDocument();
};

