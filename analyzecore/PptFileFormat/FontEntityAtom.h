#pragma once

class PptFileFormat_API FontEntityAtom
	: public Record
{
public:
	FontEntityAtom();
	FontEntityAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~FontEntityAtom();

public:
	wstring TypeFace;
};

