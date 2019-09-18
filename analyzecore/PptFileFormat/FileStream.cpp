#include "stdafx.h"
#include "BaseStream.h"
#include "FileStream.h"


FileStream::FileStream()
{
}


FileStream::FileStream(const wstring& fileName)
{
	_spStream = make_shared<simple::file_ostream>(fileName.c_str());
}

FileStream::~FileStream()
{
	//析构直接释放_spStream, 文件直接close
}

size_t FileStream::Write(const unsigned char* p, size_t size)
{
	if (_spStream == nullptr)
		return 0;

	return _spStream->write(p, size);
}

size_t FileStream::Write(const char* p, size_t size)
{
	if (_spStream == nullptr)
		return 0;

	_spStream->write(p, size);

	//TODO:返回值
	return 0;
}

bool FileStream::Close()
{
	if (_spStream == nullptr)
		return false;

	_spStream->close();

	return true;
}
