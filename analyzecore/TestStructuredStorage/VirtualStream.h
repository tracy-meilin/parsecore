#pragma once

class VirtualStream
	: public BaseStream
{
public:
	VirtualStream();
	VirtualStream(shared_ptr<AbstractFat> spFat, unsigned long startSector, __int64 sizeOfStream, wstring name);
	virtual ~VirtualStream();

	virtual int Read(unsigned char* p, int offset, size_t size) override;

	virtual int Read(char* p, int offset, size_t size) override;

	virtual __int64 Seek(__int64 offset, int way) override;

	// get/set
	virtual __int64 GetPosition() override{ return _position; }
	virtual void SetPosition(__int64 position) override{ _position = position; }

	virtual __int64 GetLength() override{ return _length; }

	//TODO: ‘›Œ¥ µœ÷
	virtual size_t Write(const unsigned char* p, size_t size) override { return 0; };

	virtual size_t Write(const char* p, size_t size) override { return 0; };

	//////////////////////////////////////////////////////////////////////////

	unsigned short ReadUInt16();

	unsigned long ReadUInt32();

	int Read(unsigned char* p, size_t size);

	int Read(unsigned char* p, int offset, size_t size, __int64 position);

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

