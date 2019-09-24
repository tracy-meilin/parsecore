#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "ParagraphRunTabStop.h"
#include "GrColorAtom.h"
#include "CharacterRun.h"
#include "Record.h"
#include "TextCFExceptionAtom.h"


TextCFExceptionAtom::TextCFExceptionAtom()
{
}

TextCFExceptionAtom::TextCFExceptionAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	_spRun = make_shared<CharacterRun>(_spBinaryReader);
}


TextCFExceptionAtom::~TextCFExceptionAtom()
{
}
