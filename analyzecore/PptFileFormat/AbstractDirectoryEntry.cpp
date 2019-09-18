#include "stdafx.h"
#include "GlobalDefines.h"
#include "AbstractDirectoryEntry.h"


AbstractDirectoryEntry::AbstractDirectoryEntry()
{
	_sid = 0x0;
}


AbstractDirectoryEntry::AbstractDirectoryEntry(unsigned long sid)
{
	_sid = sid;
}

AbstractDirectoryEntry::~AbstractDirectoryEntry()
{
}
