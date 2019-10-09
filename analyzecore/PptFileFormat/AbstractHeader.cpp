#include "stdafx.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "AbstractHeader.h"
#include <math.h>


AbstractHeader::AbstractHeader()
{
}


AbstractHeader::~AbstractHeader()
{
}

void AbstractHeader::SetSectorShift(unsigned short value)
{
	_sectorShift = value;
	// Calculate sector size
	_sectorSize = (unsigned short)pow((double)2, (double)_sectorShift);
	if (_sectorShift != 9 && _sectorShift != 12)
	{
		// TODO: error
	}
}

void AbstractHeader::SetMiniSectorShit(unsigned short value)
{
	_miniSectorShift = value;

	// Calculate mini sector size
	_miniSectorSize = (unsigned short)pow((double)2, (double)_miniSectorShift);
	if (_miniSectorShift != 6)
	{
		// TODO: error
	}
}
