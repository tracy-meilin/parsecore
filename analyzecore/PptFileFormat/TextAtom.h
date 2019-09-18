#pragma once

#include "ITextDataRecord.h"

class PptFileFormat_API TextAtom
	: public Record
	, public ITextDataRecord
{
public:
	TextAtom();
	TextAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance,
		Encoding encoding);
	~TextAtom();

	virtual wstring ToString(unsigned long depth) override{ return _T(""); };

public:
	wstring Text;
	shared_ptr<TextHeaderAtom> _spTextHeaderAtom = nullptr;
};

