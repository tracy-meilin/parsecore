#pragma once

class TextHeaderAtom;
class ITextDataRecord
{
public:
	ITextDataRecord();
	~ITextDataRecord();

	virtual wstring ToString(unsigned long depth);

public:
	shared_ptr<TextHeaderAtom> _spTextHeaderAtom = nullptr;
};

