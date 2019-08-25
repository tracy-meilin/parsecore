#pragma once
class BaseStream
{
public:
	BaseStream();
	virtual ~BaseStream();

	virtual int Read(unsigned char* p, int offset, size_t size) = 0;

	virtual int Read(char* p, int offset, size_t size) = 0;

	virtual __int64 GetPosition() = 0;
	virtual void SetPosition(__int64 position) = 0;

	virtual __int64 GetLength() = 0;

	virtual __int64 Seek(__int64 offset, int way) = 0;
};

