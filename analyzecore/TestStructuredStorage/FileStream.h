#pragma once

class FileStream
	: public BaseStream
{
public:
	FileStream();
	FileStream(const wstring& fileName);
	virtual ~FileStream();

	virtual int Read(unsigned char* p, int offset, size_t size) override{ return 0; };

	virtual int Read(char* p, int offset, size_t size) override{ return 0; };

	virtual __int64 GetPosition() override { return 0; };
	virtual void SetPosition(__int64 position) override {};

	virtual __int64 GetLength() override { return 0; };

	virtual __int64 Seek(__int64 offset, int way) override { return 0; };

	//write
	virtual size_t Write(const unsigned char* p, size_t size) override;

	virtual size_t Write(const char* p, size_t size) override;

	virtual bool Close() override;

private:
	shared_ptr<simple::file_ostream<std::true_type>> _spStream = nullptr;
};

