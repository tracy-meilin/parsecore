#pragma once

class Slide 
	: public RegularContainer
{
public:
	Slide();
	Slide(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Slide();

public:
	shared_ptr<SlidePersistAtom> spPersistAtom = nullptr;
};

