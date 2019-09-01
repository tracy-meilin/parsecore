#pragma once
class TextPFExceptionAtom 
	: public Record
{
public:
	TextPFExceptionAtom();
	TextPFExceptionAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~TextPFExceptionAtom();

public:
	shared_ptr<ParagraphRun> _spRun;
};

