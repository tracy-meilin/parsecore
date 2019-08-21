#include "stdafx.h"
#include "SimpleBinStream.h"
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
