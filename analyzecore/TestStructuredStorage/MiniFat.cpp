#include "stdafx.h"
#include "SimpleBinStream.h"
#include "GlobalDefines.h"
#include "InternalBitConverter.h"
#include "AbstractHeader.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"
#include "MiniFat.h"

#include <math.h>


MiniFat::MiniFat()
{
}


MiniFat::MiniFat(shared_ptr<Fat> spFat, 
	shared_ptr<Header> spHeader, 
	shared_ptr<InputHandler> spFileHandler,
	unsigned long miniStreamStart, 
	unsigned __int64 sizeOfMiniStream)
	: AbstractFat(spHeader, spFileHandler)
{
	_spFat = spFat;
	_miniStreamStart = miniStreamStart;
	_sizeOfMiniStream = sizeOfMiniStream;

	Init();
}

MiniFat::~MiniFat()
{
}

/// <summary>
/// Returns the next sector in a chain
/// </summary>
/// <param name="currentSector">The current sector in the chain</param>
/// <returns>The next sector in the chain</returns>
unsigned long MiniFat::GetNextSectorInChain(unsigned long currentSector)
{
	unsigned long sectorInFile = _sectorsUsedByMiniFat[(int)(currentSector / _addressesPerSector)];
	// calculation of position:
	// currentSector % _addressesPerSector = number of address in the sector address
	// address uses 32 bit = 4 bytes
	_spFileHandler->SeekToPositionInSector(sectorInFile, 4 * ((int)currentSector % _addressesPerSector));
	return _spFileHandler->ReadUInt32();
}

/// <summary>
/// Seeks to a given position in a sector of the mini stream
/// </summary>
/// <param name="sector">The sector to seek to</param>
/// <param name="position">The position in the sector to seek to</param>
/// <returns>The new position in the stream.</returns>
long MiniFat::SeekToPositionInSector(__int64 sector, __int64 position)
{
	int sectorInMiniStreamChain = (int)((sector * _spHeader->_miniSectorSize) / _spFat->GetSectorSize());
	int offsetInSector = (int)((sector *  _spHeader->_miniSectorSize) / _spFat->GetSectorSize());

	if (position < 0)
	{
		//throw new ArgumentOutOfRangeException("position");
	}

	return _spFileHandler->SeekToPositionInSector(_sectorsUsedByMiniStream[sectorInMiniStreamChain], offsetInSector + position);
}

void MiniFat::Init()
{
	ReadSectorsUsedByMiniFAT();
	ReadSectorsUsedByMiniStream();
	CheckConsistency();
}

/// <summary>
/// Reads the sectors used by the MiniFat
/// </summary>
void MiniFat::ReadSectorsUsedByMiniFAT()
{
	if (_spHeader->_miniFatStartSector == Common::SectorId::ENDOFCHAIN 
		|| _spHeader->_noSectorsInMiniFatChain == 0x0)
	{
		return;
	}

	_sectorsUsedByMiniFat = _spFat->GetSectorChain(_spHeader->_miniFatStartSector, _spHeader->_noSectorsInMiniFatChain, _T("MiniFat"));
}

/// <summary>
/// Reads the sectors used by the MiniFat
/// </summary>
void MiniFat::ReadSectorsUsedByMiniStream()
{
	if (_miniStreamStart == Common::SectorId::ENDOFCHAIN)
	{
		return;
	}
	_sectorsUsedByMiniStream = _spFat->GetSectorChain(_miniStreamStart, (unsigned __int64)ceil((double)_sizeOfMiniStream / _spHeader->_sectorSize), _T("MiniStream"));
}

/// <summary>
/// Checks whether the size specified in the header matches the actual size
/// </summary>
void MiniFat::CheckConsistency()
{
	if (_sectorsUsedByMiniFat.size() != _spHeader->_noSectorsInMiniFatChain)
	{
		//throw new ChainSizeMismatchException("MiniFat");
	}

	if (_sectorsUsedByMiniStream.size() != ceil((double)_sizeOfMiniStream / _spHeader->_sectorSize))
	{
		//throw new ChainSizeMismatchException("MiniStream");
	}
}
