#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"


PersistDirectoryAtom::PersistDirectoryAtom()
{
}


PersistDirectoryAtom::PersistDirectoryAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	while (_spBinaryReader->GetPosition() != _spBinaryReader->GetLength())
	{
		this->PersistDirEntries.push_back(make_shared<PersistDirectoryEntry>(_spBinaryReader));
	}
}

PersistDirectoryAtom::~PersistDirectoryAtom()
{
}
