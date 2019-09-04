#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "OEPlaceHolderAtom.h"


OEPlaceHolderAtom::OEPlaceHolderAtom()
{
}


OEPlaceHolderAtom::OEPlaceHolderAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->Position = _spBinaryReader->ReadInt32();
	unsigned char Tmp;
	_spBinaryReader->Read(&Tmp, 1);
	this->PlacementId = (OEPlaceHolderAtomSpace::PlaceholderEnum)Tmp;
	spBinaryReader->Read(&this->PlaceholderSize, 1);
	// Throw away additional junk
	_spBinaryReader->ReadUInt16();
}

OEPlaceHolderAtom::~OEPlaceHolderAtom()
{
}

bool OEPlaceHolderAtom::IsObjectPlaceholder()
{
	return this->PlacementId == OEPlaceHolderAtomSpace::Object;
}
