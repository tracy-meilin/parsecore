#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "BlipStoreEntry.h"


BlipStoreEntry::BlipStoreEntry()
{
}


BlipStoreEntry::BlipStoreEntry(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	char tmp;
	_spBinaryReader->Read(&tmp, 1);
	this->btWin32 = (BlipStoreSpace::BlipType)tmp;
	_spBinaryReader->Read(&tmp, 1);
	this->btMacOS = (BlipStoreSpace::BlipType)tmp;

	this->rgbUid = new unsigned char[16];
	_spBinaryReader->Read(this->rgbUid, 16);

	this->tag = _spBinaryReader->ReadInt16();
	this->size = _spBinaryReader->ReadUInt32();
	this->cRef = _spBinaryReader->ReadUInt32();
	this->foDelay = _spBinaryReader->ReadUInt32();
	_spBinaryReader->Read(&tmp, 1);
	this->usage = (BlipStoreSpace::BlipUsage)tmp;
	_spBinaryReader->Read(&this->cbName, 1);
	_spBinaryReader->Read(&this->unused2, 1);
	_spBinaryReader->Read(&this->unused3, 1);
}

BlipStoreEntry::~BlipStoreEntry()
{
}
