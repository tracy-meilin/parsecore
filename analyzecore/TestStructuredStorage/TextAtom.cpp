#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "TabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "TextStyleAtom.h"
#include "TextHeaderAtom.h"
#include "ITextDataRecord.h"
#include "TextAtom.h"


TextAtom::TextAtom()
{
}

TextAtom::TextAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	unsigned char* bytes = new unsigned char[size];
	_spBinaryReader->Read(bytes, size);
	//TODO: зЊТы
}


TextAtom::~TextAtom()
{
}
