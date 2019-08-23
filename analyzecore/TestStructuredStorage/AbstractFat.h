#pragma once

class AbstractFat
{
public:
	AbstractFat();
	AbstractFat(shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler);
	~AbstractFat();

	/// <summary>
	/// Returns the next sector in a chain
	/// </summary>
	/// <param name="currentSector">The current sector in the chain</param>
	/// <returns>The next sector in the chain</returns>
	virtual unsigned long GetNextSectorInChain(unsigned long currentSector) = 0;

	/// <summary>
	/// Seeks to a given position in a sector
	/// </summary>
	/// <param name="sector">The sector to seek to</param>
	/// <param name="position">The position in the sector to seek to</param>
	/// <returns></returns>
	virtual long SeekToPositionInSector(__int64 sector, __int64 position) = 0;

	virtual unsigned short GetSectorSize() = 0;

	vector<unsigned long> GetSectorChain(unsigned long startSector, unsigned __int64 maxCount, wstring name);

	vector<unsigned long> GetSectorChain(unsigned long startSector, unsigned __int64 maxCount, wstring name, bool immediateCycleCheck);

	int UncheckedRead(unsigned char* array, int offset, int count);

	int UncheckedReadByte();

protected:
	shared_ptr<Header> _spHeader = nullptr;
	shared_ptr<InputHandler> _spFileHandler = nullptr;
	int _addressesPerSector;


};

