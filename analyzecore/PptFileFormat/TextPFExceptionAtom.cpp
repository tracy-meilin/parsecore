#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "TabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "Record.h"
#include "TextPFExceptionAtom.h"


TextPFExceptionAtom::TextPFExceptionAtom()
{
}


TextPFExceptionAtom::TextPFExceptionAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	_spBinaryReader->ReadInt16();
	_spRun = make_shared<ParagraphRun>(_spBinaryReader, true);
}

TextPFExceptionAtom::~TextPFExceptionAtom()
{
}
