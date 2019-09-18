#pragma once
#include "ITextDataRecord.h"

class PptFileFormat_API TextStyleAtom
	: public Record 
	, public ITextDataRecord
{
public:
	TextStyleAtom();
	TextStyleAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~TextStyleAtom();

	virtual void AfterTextHeaderSet(){};

	//get/set
	shared_ptr<TextHeaderAtom> GetTextHeaderAtom(){ return _spTextHeaderAtom; }
	void SetTextHeaderAtom(shared_ptr<TextHeaderAtom> spAtom){ _spTextHeaderAtom = spAtom; AfterTextHeaderSet(); }

public:
	vector<shared_ptr<ParagraphRun>> m_vecPRuns;
	vector<shared_ptr<CharacterRun>> m_vecCRuns;

private:
	shared_ptr<TextHeaderAtom> _spTextHeaderAtom = nullptr;
};

