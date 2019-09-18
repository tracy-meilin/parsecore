#include "stdafx.h"
#include "GlobalDefines.h"
#include "InternalBitConverter.h"
#include "AbstractHeader.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "Header.h"
#include "AbstractFat.h"


AbstractFat::AbstractFat()
{
}


AbstractFat::AbstractFat(shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler)
{
	_spHeader = spHeader;
	_spFileHandler = spFileHandler;
	_addressesPerSector = spHeader->_sectorSize / 4;
}

AbstractFat::~AbstractFat()
{
}

std::vector<unsigned long> AbstractFat::GetSectorChain(unsigned long startSector, unsigned __int64 maxCount, wstring name)
{
	return GetSectorChain(startSector, maxCount, name, false);
}

std::vector<unsigned long> AbstractFat::GetSectorChain(unsigned long startSector, unsigned __int64 maxCount, wstring name, bool immediateCycleCheck)
{
	vector<unsigned long> result;
	result.push_back(startSector);

	while (true)
	{
		unsigned long nextSectorInStream = this->GetNextSectorInChain(result[result.size() - 1]);
		// Check for invalid sectors in chain
		if (nextSectorInStream == Common::SectorId::DIFSECT
			|| nextSectorInStream == Common::SectorId::FATSECT
			|| nextSectorInStream == Common::SectorId::FREESECT)
			return result;

		if (nextSectorInStream == Common::SectorId::ENDOFCHAIN)
			break;

		if (immediateCycleCheck)
		{
			for (auto ele : result)
			{
				if (ele == nextSectorInStream)
				{
					return result;
				}
			}
		}

		result.push_back(nextSectorInStream);

		// Chain too long
		if (result.size() > maxCount)
		{
			//throw new ChainSizeMismatchException(name);
		}
	}

	return result;
}

int AbstractFat::UncheckedRead(unsigned char* array, int offset, int count)
{
	return _spFileHandler->UncheckedRead(array, offset, count);
}

int AbstractFat::UncheckedReadByte()
{
	return _spFileHandler->UncheckedReadByte();
}
