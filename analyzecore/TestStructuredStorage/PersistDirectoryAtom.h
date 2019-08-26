#pragma once

class PersistDirectoryAtom 
	: public Record
{
public:
	PersistDirectoryAtom();
	PersistDirectoryAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~PersistDirectoryAtom();

public:
	vector<shared_ptr<PersistDirectoryEntry>> PersistDirEntries;
};

