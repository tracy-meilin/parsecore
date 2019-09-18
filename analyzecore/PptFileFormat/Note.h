#pragma once

class PptFileFormat_API Note
	: public RegularContainer
{
public:
	Note();
	Note(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Note();

public:
	shared_ptr<SlidePersistAtom> _spPersistAtom = nullptr;
};

