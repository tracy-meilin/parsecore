#pragma once

class OutlineTextRefAtom 
	: public Record
{
public:
	OutlineTextRefAtom();
	OutlineTextRefAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~OutlineTextRefAtom();

public:
	signed short Index;
};

