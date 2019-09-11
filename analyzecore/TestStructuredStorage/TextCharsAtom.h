#pragma once

class TextCharsAtom 
	: public TextAtom
{
public:
	TextCharsAtom();
	TextCharsAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~TextCharsAtom();
};

