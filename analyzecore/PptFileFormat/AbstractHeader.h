#pragma once

class AbstractIOHandler;
class PptFileFormat_API AbstractHeader
{
public:
	AbstractHeader();
	~AbstractHeader();

	virtual void GetVirtual() = 0;

	void SetSectorShift(unsigned short value);
	unsigned short GetSectorShift(){ return _sectorShift; }

	void SetMiniSectorShit(unsigned short value);
	unsigned short GetMiniSectorShit(){ return _miniSectorShift; }

protected:
	unsigned __int64 MAGIC_NUMBER = 0xE11AB1A1E011CFD0;

	shared_ptr<AbstractIOHandler> _spIoHandler;

public:
	//
	unsigned short _sectorSize;
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

private:
	// Sector shift and sector size
	unsigned short _sectorShift;
	// Minisector shift and Minisector size
	unsigned short _miniSectorShift;
};

