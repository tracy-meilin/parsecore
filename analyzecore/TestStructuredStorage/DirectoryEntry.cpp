#include "stdafx.h"
#include "GlobalDefines.h"
#include "SimpleBinStream.h"
#include "AbstractDirectoryEntry.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "DirectoryEntry.h"


DirectoryEntry::DirectoryEntry()
{
}


DirectoryEntry::DirectoryEntry(shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler, unsigned long sid, wstring path)
	: AbstractDirectoryEntry(sid)
{
	_spHeader = spHeader;
	_spFileHandler = spFileHandler;
	ReadDirectoryEntry();
	_path = path;
}

DirectoryEntry::~DirectoryEntry()
{
}

void DirectoryEntry::ReadDirectoryEntry()
{
	_name = _spFileHandler->ReadString(64);

	// Name length check: lengthOfName = length of the element in bytes including Unicode NULL
	unsigned short lengthOfName = _spFileHandler->ReadUInt16();
	char tmp;
	_spFileHandler->ReadChar(tmp);
	_type = (Common::DirectoryEntryType)tmp;
}
