#pragma once
class FontCollection 
	: public RegularContainer
{
public:
	FontCollection();
	FontCollection(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);

	~FontCollection();

public:
	vector<shared_ptr<FontEntityAtom>> entities;
};

