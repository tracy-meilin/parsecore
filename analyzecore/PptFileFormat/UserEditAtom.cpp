#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "UserEditAtom.h"


UserEditAtom::UserEditAtom()
{
}


UserEditAtom::UserEditAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->LastSlideIdRef = _spBinaryReader->ReadUInt32();
	this->BuildVersion = _spBinaryReader->ReadUInt16();

	char tmp;
	_spBinaryReader->Read(&tmp, 1);
	this->MajorVersion = tmp;
	_spBinaryReader->Read(&tmp, 1);
	this->MajorVersion = tmp;

	this->OffsetLastEdit = _spBinaryReader->ReadUInt32();
	this->OffsetPersistDirectory = _spBinaryReader->ReadUInt32();
	this->DocPersistIdRef = _spBinaryReader->ReadUInt32();
	this->PersistIdSeed = _spBinaryReader->ReadUInt32();
	this->LastView = _spBinaryReader->ReadUInt16();

	// Throw away reserved data
	_spBinaryReader->ReadUInt16();

	if (_spBinaryReader->GetPosition() != _spBinaryReader->GetLength())
	{
		this->EncryptSessionPersistIdRef = _spBinaryReader->ReadUInt32();
	}
}

UserEditAtom::~UserEditAtom()
{
}
