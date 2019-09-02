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
	virtual ~Slide();

	virtual wstring ToString(unsigned long depth) override{ return _T(""); };

public:
	shared_ptr<SlidePersistAtom> spPersistAtom = nullptr;
};

