#pragma once
class SlidePersisAtom 
	: public Record
{
public:
	SlidePersisAtom();
	SlidePersisAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~SlidePersisAtom();
};

