#include "stdafx.h"
#include "GlobalDefines.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractHeader.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"


Fat::Fat()
{
}


Fat::Fat(shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler)
	: AbstractFat(spHeader, spFileHandler)
{
	Init();
}

Fat::~Fat()
{
}

unsigned long Fat::GetNextSectorInChain(unsigned long currentSector)
{
	unsigned long sectorInFile = _sectorsUsedByFat[(int)(currentSector / _addressesPerSector)];
	
		//_sectorsUsedByFat[(int)(currentSector / _addressesPerSector)];
	// calculation of position:
	// currentSector % _addressesPerSector = number of address in the sector address
	// address uses 32 bit = 4 bytes
	_spFileHandler->SeekToPositionInSector(sectorInFile, 4 * (currentSector % _addressesPerSector));
	return _spFileHandler->ReadUInt32();
}

void Fat::Init()
{
	ReadFirst109SectorsUsedByFAT();
	ReadSectorsUsedByFatFromDiFat();
	CheckConsistency();
}

void Fat::ReadFirst109SectorsUsedByFAT()
{
	if (_spFileHandler == nullptr)
		return;

	_spFileHandler->SeekToPositionInSector(-1, 0x4C);
	unsigned long fatSector;

	for (int i = 0; i < 109; ++i)
	{
		fatSector = _spFileHandler->ReadUInt32();

		if (fatSector == Common::SectorId::FREESECT)
			break;

		_sectorsUsedByFat.push_back(fatSector);
	}
}

void Fat::ReadSectorsUsedByFatFromDiFat()
{
	if (_spHeader->_diFatStartSector == Common::SectorId::ENDOFCHAIN
		|| _spHeader->_noSectorsInDiFatChain == 0x0)
		return;

	_spFileHandler->SeekToSector(_spHeader->_diFatStartSector);
	bool lastFatSectorFound = false;
	_sectorsUsedByFat.push_back(_spHeader->_diFatStartSector);

	while (true)
	{
		for (int i = 0; i < _addressesPerSector - 1; ++i)
		{
			unsigned long fatSector = _spFileHandler->ReadUInt32();
			if (fatSector == Common::SectorId::FREESECT)
			{
				lastFatSectorFound = true;
				break;
			}

			_sectorsUsedByFat.push_back(fatSector);
		}

		if (lastFatSectorFound)
			break;

		unsigned long nextDiFatSector = _spFileHandler->ReadUInt32();
		if (nextDiFatSector == Common::SectorId::FREESECT 
			|| nextDiFatSector == Common::SectorId::ENDOFCHAIN)
			break;

		_sectorsUsedByDiFat.push_back(nextDiFatSector);
		_spFileHandler->SeekToSector(nextDiFatSector);

		if (_sectorsUsedByDiFat.size() > _spHeader->_noSectorsInDiFatChain)
			return;
	}
}

void Fat::CheckConsistency()
{
	int n = _spHeader->_noSectorsInFatChain;

	if (_sectorsUsedByDiFat.size() != _spHeader->_noSectorsInDiFatChain
		|| _sectorsUsedByFat.size() != _spHeader->_noSectorsInFatChain)
		return;
}
