#pragma once

class PptFileFormat_API TextCFExceptionAtom
	: public Record
{
public:
	TextCFExceptionAtom();

	TextCFExceptionAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~TextCFExceptionAtom();

public:
	shared_ptr<CharacterRun> _spRun;
};

