#pragma once

/// <summary>
/// Represents the Fat in a compound file
/// Author: math
/// </summary>
class PptFileFormat_API Fat
	: public AbstractFat
{
public:
	Fat();
	Fat(shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler);
	~Fat();

	virtual unsigned long GetNextSectorInChain(unsigned long currentSector) override;

	virtual long SeekToPositionInSector(__int64 sector, __int64 position) override;

	virtual unsigned short GetSectorSize() override { return _spHeader->_sectorSize; }

private:
	void Init();

	void ReadFirst109SectorsUsedByFAT();

	void ReadSectorsUsedByFatFromDiFat();

	void CheckConsistency();

private:
	vector<unsigned long> _sectorsUsedByFat;
	vector<unsigned long> _sectorsUsedByDiFat;
};

