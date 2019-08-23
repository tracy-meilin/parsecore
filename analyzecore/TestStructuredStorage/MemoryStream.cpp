#include "stdafx.h"
#include "SimpleBinStream.h"
#include "BaseStream.h"
#include "MemoryStream.h"


MemoryStream::MemoryStream()
{
}


MemoryStream::MemoryStream(unsigned char* byteArray, size_t size)
{
	_spStream = make_shared<simple::mem_istream<std::true_type>>(byteArray, size);
}

MemoryStream::~MemoryStream()
{
}

int MemoryStream::Read(unsigned char* p, int offset, size_t size)
{
	return _spStream->read(p, size);
}

int MemoryStream::Read(char* p, int offset, size_t size)
{
	return _spStream->read(p, size);
}
