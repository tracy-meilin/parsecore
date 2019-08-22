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
	_name = _spFileHandler->ReadUnicodeString(32);

	// Name length check: lengthOfName = length of the element in bytes including Unicode NULL
	unsigned short lengthOfName = _spFileHandler->ReadUInt16();
	char tmp;
	_spFileHandler->ReadChar(tmp);
	_type = (Common::DirectoryEntryType)tmp;
	_spFileHandler->ReadChar(tmp);
	_color = (Common::DirectoryEntryColor)tmp;
	_leftSiblingSid = _spFileHandler->ReadUInt32();
	_rightSiblingSid = _spFileHandler->ReadUInt32();
	_childSiblingSid = _spFileHandler->ReadUInt32();
	// TODO: char to GUID
	char byteArray[16] = { 0 };
	_spFileHandler->Read(byteArray, 16);

	_userFlags = _spFileHandler->ReadUInt32();
	// Omit creation time
	_spFileHandler->ReadUInt64();
	// Omit modification time 
	_spFileHandler->ReadUInt64();
	_startSector = _spFileHandler->ReadUInt32();

	unsigned long sizeLow = _spFileHandler->ReadUInt32();
	unsigned long sizeHigh = _spFileHandler->ReadUInt32();

	if (_spHeader->_sectorSize == 512 && sizeHigh != 0x0)
	{
		// Must be zero according to the specification. However, this requirement can be ommited.
		//TraceLogger.Warning("ul_SizeHigh of stream '" + Name + "' should be zero as sector size is 512.");
		sizeHigh = 0x0;
	}

	_sizeOfStream = ((unsigned __int64)sizeHigh << 32) + sizeLow;
}
