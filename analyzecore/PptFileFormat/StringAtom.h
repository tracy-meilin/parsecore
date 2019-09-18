#pragma once
class CStringAtom 
	: public Record
{
public:
	CStringAtom();
	CStringAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~CStringAtom();

public:
	wstring Text;
};

