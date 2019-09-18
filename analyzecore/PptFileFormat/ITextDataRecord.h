#pragma once

class TextHeaderAtom;
class PptFileFormat_API ITextDataRecord
{
public:
	ITextDataRecord();
	~ITextDataRecord();

	virtual wstring ToString(unsigned long depth);

public:
	shared_ptr<TextHeaderAtom> _spTextHeaderAtom = nullptr;
};

