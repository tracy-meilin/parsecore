#pragma once

class PptFileFormat_API UserEditAtom
	: public Record
{
public:
	UserEditAtom();
	UserEditAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~UserEditAtom();

public:
	unsigned long LastSlideIdRef;
	unsigned short BuildVersion;
	char MinorVersion;
	char MajorVersion;
	unsigned long OffsetLastEdit;
	unsigned long OffsetPersistDirectory;
	unsigned long DocPersistIdRef;
	unsigned long PersistIdSeed;
	unsigned short LastView;
	unsigned long EncryptSessionPersistIdRef;
};

