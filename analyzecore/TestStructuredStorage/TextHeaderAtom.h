#pragma once

#include "ITextDataRecord.h"
#include "TextStyleAtom.h"

class TextAtom;
class TextHeaderAtom 
	: public Record
{
public:
	TextHeaderAtom();
	TextHeaderAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~TextHeaderAtom();

	void HandleTextDataRecord(shared_ptr<ITextDataRecord> spTdRecord);

public:
	Common::TextType TextType;
	shared_ptr<TextAtom> _spTextAtom = nullptr;
	shared_ptr<TextStyleAtom> _spTextStyleAtom = nullptr;
};

