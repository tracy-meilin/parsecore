#include "stdafx.h"
#include "GlobalDefines.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "VirtualStream.h"
#include <math.h>


VirtualStream::VirtualStream()
{
}


VirtualStream::VirtualStream(shared_ptr<AbstractFat> spFat, unsigned long startSector, __int64 sizeOfStream, wstring name)
{
	_spFat = spFat;
	_length = sizeOfStream;
	_name = name;
	if (startSector == Common::SectorId::ENDOFCHAIN || _length == 0)
	{
		return;
	}

	Init(startSector);
}

VirtualStream::~VirtualStream()
{
}

void VirtualStream::Init(unsigned long startSector)
{
	_sectors = _spFat->GetSectorChain(startSector, (unsigned __int64)ceil((double)_length / _spFat->GetSectorSize()), _name);
	CheckConsistency();
}

void VirtualStream::CheckConsistency()
{
	if (((unsigned __int64)_sectors.size()) != ceil((double)_length / _spFat->GetSectorSize()))
	{
		//throw new ChainSizeMismatchException(_name);
	}
}
