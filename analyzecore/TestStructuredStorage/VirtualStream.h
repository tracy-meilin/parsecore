#pragma once

class VirtualStream
{
public:
	VirtualStream();
	VirtualStream(shared_ptr<AbstractFat> spFat, unsigned long startSector, __int64 sizeOfStream, wstring name);
	~VirtualStream();

	unsigned short ReadUInt16();

	unsigned long ReadUInt32();

	int Read(unsigned char* p, size_t size);

	int Read(unsigned char* p, int offset, size_t size);

	int Read(unsigned char* p, int offset, size_t size, __int64 position);

	// get/set
	__int64 GetPosition(){ return _position; }
	void SetPosition(__int64 position){ _position = position; }

	__int64 GetLength(){ return _length; }

private:
	void Init(unsigned long startSector);

	void CheckConsistency();

protected:
	__int64 _position = 0;
	__int64 _length;

private:
	wstring _name;
	vector<unsigned long> _sectors;
	shared_ptr<AbstractFat> _spFat = nullptr;
};

