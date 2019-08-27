#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "SlidePersistAtom.h"


SlidePersistAtom::SlidePersistAtom()
{
}


SlidePersistAtom::SlidePersistAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->PersistIdRef = _spBinaryReader->ReadUInt32();
	this->Flags = _spBinaryReader->ReadUInt32();
	this->NumberText = _spBinaryReader->ReadInt32();
	this->SlideId = _spBinaryReader->ReadUInt32();
	_spBinaryReader->ReadUInt32();	// Throw away reserved field
}

SlidePersistAtom::~SlidePersistAtom()
{
}
