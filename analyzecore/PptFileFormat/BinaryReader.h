#pragma once

class PptFileFormat_API BinaryReader
{
public:
	BinaryReader();
	BinaryReader(shared_ptr<BaseStream> spBaseStream);
	~BinaryReader();

	unsigned short ReadUInt16();

	signed short ReadInt16();

	unsigned long ReadUInt32();

	signed long ReadInt32();

	__int64 ReadInt64();

	unsigned __int64 ReadUInt64();

	float ReadSingle();

	double ReadDouble();

	bool ReadBoolean();

	int Read(unsigned char* p, int offset, size_t size);

	int Read(char* p, int offset, size_t size);

	int Read(unsigned char* p, size_t size);

	int Read(char* p, size_t size);

	string ReadString(size_t size);

	wstring ReadUnicodeString(size_t size);

	__int64 Seek(__int64 offset, int way);

	// get/set
	__int64 GetPosition();
	void SetPosition(__int64 position);

	__int64 GetLength();

protected:
	shared_ptr<BaseStream> _spBaseStream = nullptr;
};

