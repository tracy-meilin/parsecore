#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "FontEntityAtom.h"


FontEntityAtom::FontEntityAtom()
{
}

FontEntityAtom::FontEntityAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	TypeFace = _spBinaryReader->ReadUnicodeString(64 / 2);

	unsigned char lfCharSet;
	unsigned char firstbyte;
	unsigned char secondbyte;
	unsigned char lfPitchAndFamily;

	_spBinaryReader->Read(&lfCharSet, 1);
	_spBinaryReader->Read(&firstbyte, 1);
	_spBinaryReader->Read(&secondbyte, 1);
	_spBinaryReader->Read(&lfPitchAndFamily, 1);
}


FontEntityAtom::~FontEntityAtom()
{
}
