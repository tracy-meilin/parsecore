#pragma once

class PptFileFormat_API MemoryStream
	: public BaseStream
{
public:
	MemoryStream();
	MemoryStream(unsigned char* byteArray, size_t size);
	~MemoryStream();

	virtual int Read(unsigned char* p, int offset, size_t size) override;

	virtual int Read(char* p, int offset, size_t size) override;

	virtual __int64 Seek(__int64 offset, int way) override;

	// get/set
	virtual __int64 GetPosition() override{ return _spStream->getIndex(); }
	virtual void SetPosition(__int64 position) override{ _spStream->setIndex(position); }

	virtual __int64 GetLength() override{ return _spStream->getLength(); }

	//TODO: ‘›Œ¥ µœ÷
	virtual size_t Write(const unsigned char* p, size_t size) override { return 0; };

	virtual size_t Write(const char* p, size_t size) override { return 0; };

	virtual bool Close() override{ return true; };

private:
	shared_ptr<simple::mem_istream> _spStream = nullptr;
};

