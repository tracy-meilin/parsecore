#include "stdafx.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "VirtualStream.h"
#include "Record.h"

#include "CurrentUserAtom.h"


CurrentUserAtom::CurrentUserAtom()
{
}


CurrentUserAtom::CurrentUserAtom(shared_ptr<VirtualStream> spVirtualStream, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spVirtualStream, size, typeCode, version, instance)
{

}

CurrentUserAtom::~CurrentUserAtom()
{
}

std::wstring CurrentUserAtom::ToString(unsigned long depth)
{
	return _T("");
}
