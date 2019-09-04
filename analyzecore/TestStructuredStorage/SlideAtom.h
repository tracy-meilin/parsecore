#pragma once

class SlideAtom 
	: public Record
{
public:
	SlideAtom();
	SlideAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~SlideAtom();

public:
	shared_ptr<SSlideLayoutAtom> _spLayout;
	unsigned long MasterId;
	signed long NotesId;
	unsigned short Flags;
};

