#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "PersistDirectoryEntry.h"


PersistDirectoryEntry::PersistDirectoryEntry()
{
}


PersistDirectoryEntry::PersistDirectoryEntry(shared_ptr<BinaryReader> spBinaryReader)
{
	unsigned long StartPersistIdAndPersistCount = spBinaryReader->ReadUInt32();
	this->StartPersistId = (StartPersistIdAndPersistCount & 0x000FFFFFU); // First 20 bit
	this->PersistCount = (StartPersistIdAndPersistCount & 0xFFF00000U) >> 20; // Last 12 bit

	for (int i = 0; i < this->PersistCount; i++)
	{
		this->PersistOffsetEntries.push_back(spBinaryReader->ReadUInt32());
	}
}

PersistDirectoryEntry::~PersistDirectoryEntry()
{
}
