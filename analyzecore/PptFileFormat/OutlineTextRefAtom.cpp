#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "OutlineTextRefAtom.h"


OutlineTextRefAtom::OutlineTextRefAtom()
{
}


OutlineTextRefAtom::OutlineTextRefAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->Index = _spBinaryReader->ReadInt32();
}

OutlineTextRefAtom::~OutlineTextRefAtom()
{
}
