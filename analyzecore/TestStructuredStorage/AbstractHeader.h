#pragma once

class AbstractIOHandler;
class AbstractHeader
{
public:
	AbstractHeader();
	~AbstractHeader();

protected:
	unsigned __int64 MAGIC_NUMBER = 0xE11AB1A1E011CFD0;

	shared_ptr<AbstractIOHandler> _spIoHandler;

private:
	// Sector shift and sector size
	unsigned long _sectorShift;
	//
	unsigned long _sectorSize;
	// Minisector shift and Minisector size
	unsigned long _miniSectorShift;
	//
	unsigned long _miniSectorSize;
	// CSectDir
	unsigned long _noSectorsInDirectoryChain4KB;
	// CSectFat
	unsigned long _noSectorsInFatChain;
	// SectDirStart
	unsigned long _directoryStartSector;
	// UInt32ULMiniSectorCutoff
	unsigned long _miniSectorCutoff;
	// SectMiniFatStart
	unsigned long _miniFatStartSector;
	// CSectMiniFat
	unsigned long _noSectorsInMiniFatChain;
	// SectDifStart
	unsigned long _diFatStartSector;
	// CSectDif
	unsigned long _noSectorsInDiFatChain;
};

