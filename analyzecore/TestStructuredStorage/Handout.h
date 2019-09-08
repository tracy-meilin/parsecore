#pragma once

class Handout 
	: public RegularContainer
{
public:
	Handout();
	Handout(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Handout();

public:
	shared_ptr<SlidePersistAtom> _spPersistAtom = nullptr;
};

