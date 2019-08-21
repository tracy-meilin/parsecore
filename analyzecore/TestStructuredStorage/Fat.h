#pragma once

/// <summary>
/// Represents the Fat in a compound file
/// Author: math
/// </summary>
class Fat 
	: public AbstractFat
{
public:
	Fat();
	Fat(shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler);
	~Fat();

	virtual unsigned long GetNextSectorInChain(unsigned long currentSector);

	unsigned short GetSectorSize(){ return _spHeader->_sectorSize; }

private:
	void Init();

	void ReadFirst109SectorsUsedByFAT();

	void ReadSectorsUsedByFatFromDiFat();

	void CheckConsistency();

private:
	vector<unsigned long> _sectorsUsedByFat;
	vector<unsigned long> _sectorsUsedByDiFat;
};

