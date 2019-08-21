#pragma once

class AbstractIOHandler;
class AbstractHeader
{
public:
	AbstractHeader();
	~AbstractHeader();

	virtual void GetVirtual() = 0;

protected:
	unsigned __int64 MAGIC_NUMBER = 0xE11AB1A1E011CFD0;

	shared_ptr<AbstractIOHandler> _spIoHandler;

public:
	// Sector shift and sector size
	unsigned short _sectorShift;
	//
	unsigned short _sectorSize;
	// Minisector shift and Minisector size
	unsigned short _miniSectorShift;
	//
	unsigned short _miniSectorSize;
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

