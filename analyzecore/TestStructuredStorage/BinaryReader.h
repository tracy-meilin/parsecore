#pragma once
class BinaryReader
{
public:
	BinaryReader();
	BinaryReader(shared_ptr<BaseStream> spBaseStream);
	~BinaryReader();

	unsigned short ReadUInt16();

	unsigned long ReadUInt32();

	int Read(unsigned char* p, int offset, size_t size);

	int Read(char* p, int offset, size_t size);

	int Read(unsigned char* p, size_t size);

	int Read(char* p, size_t size);

	string ReadString(size_t size);

	// get/set
	__int64 GetPosition();
	void SetPosition(__int64 position);

	__int64 GetLength();

protected:
	shared_ptr<BaseStream> _spBaseStream = nullptr;
};

