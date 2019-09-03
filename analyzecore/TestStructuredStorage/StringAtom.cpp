#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "StringAtom.h"


CStringAtom::CStringAtom()
{
}


CStringAtom::CStringAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->Text = _spBinaryReader->ReadUnicodeString(size / 2);
}

CStringAtom::~CStringAtom()
{
}
