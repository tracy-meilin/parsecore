#pragma once

class MiniFat 
	: public AbstractFat
{
public:
	MiniFat();
	MiniFat(shared_ptr<Fat> spFat,
		shared_ptr<Header> spHeader,
		shared_ptr<InputHandler> spFileHandler,
		unsigned long miniStreamStart,
		unsigned __int64 sizeOfMiniStream);

	~MiniFat();

	virtual unsigned long GetNextSectorInChain(unsigned long currentSector) override;

	virtual long SeekToPositionInSector(__int64 sector, __int64 position) override;

	virtual unsigned short GetSectorSize() override { return _spHeader->_miniSectorSize; }

private:
	void Init();

	void ReadSectorsUsedByMiniFAT();

	void ReadSectorsUsedByMiniStream();

	void CheckConsistency();

private:
	vector<unsigned long> _sectorsUsedByMiniFat;
	vector<unsigned long> _sectorsUsedByMiniStream;

	shared_ptr<Fat> _spFat = nullptr;
	unsigned long _miniStreamStart;
	unsigned __int64 _sizeOfMiniStream;
};

