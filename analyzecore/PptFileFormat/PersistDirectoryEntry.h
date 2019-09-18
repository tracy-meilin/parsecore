#pragma once

class PptFileFormat_API PersistDirectoryEntry
{
public:
	PersistDirectoryEntry();
	PersistDirectoryEntry(shared_ptr<BinaryReader> spBinaryReader);
	~PersistDirectoryEntry();

public:
	unsigned long StartPersistId;
	unsigned long PersistCount;
	vector<unsigned long> PersistOffsetEntries;
};

