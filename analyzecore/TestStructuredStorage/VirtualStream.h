#pragma once

class VirtualStream
{
public:
	VirtualStream();
	VirtualStream(shared_ptr<AbstractFat> spFat, unsigned long startSector, __int64 sizeOfStream, wstring name);
	~VirtualStream();

private:
	void Init(unsigned long startSector);

	void CheckConsistency();

protected:
	__int64 _position;
	__int64 _length;

private:
	wstring _name;
	vector<unsigned long> _sectors;
	shared_ptr<AbstractFat> _spFat = nullptr;
};

