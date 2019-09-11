#pragma once

class TextSIException
{
public:
	TextSIException(shared_ptr<BinaryReader> spBinaryReader);
	~TextSIException();

public:
	bool spell;
	bool lang;
	bool altLang;
	bool fPp10ext;
	bool fBidi;
	bool smartTag;
	unsigned short spellInfo;
	unsigned short lid;
	unsigned short bidi;
	unsigned short altLid;

private:
	unsigned long flags;
};

class TextSIRun
{
public:
	TextSIRun(shared_ptr<BinaryReader> spBinaryReader);
	~TextSIRun();

public:
	unsigned long count;
	shared_ptr<TextSIException> spSI = nullptr;
};




class TextSpecialInfoAtom 
	: public Record
{
public:
	TextSpecialInfoAtom();
	TextSpecialInfoAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
 	virtual ~TextSpecialInfoAtom();

public:
	vector<shared_ptr<TextSIRun>> m_vecTextSIRuns;
};

