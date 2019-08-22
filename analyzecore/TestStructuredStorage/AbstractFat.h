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

	virtual unsigned short GetSectorSize() = 0;

	vector<unsigned long> GetSectorChain(unsigned long startSector, unsigned __int64 maxCount, wstring name);

	vector<unsigned long> GetSectorChain(unsigned long startSector, unsigned __int64 maxCount, wstring name, bool immediateCycleCheck);

protected:
	shared_ptr<Header> _spHeader = nullptr;
	shared_ptr<InputHandler> _spFileHandler = nullptr;
	int _addressesPerSector;


};

