#include "stdafx.h"
#include "BaseStream.h"
#include "MemoryStream.h"


MemoryStream::MemoryStream()
{
}


MemoryStream::MemoryStream(unsigned char* byteArray, size_t size)
{
	_spStream = make_shared<simple::mem_istream>(byteArray, size);
}

MemoryStream::~MemoryStream()
{
}

int MemoryStream::Read(unsigned char* p, int offset, size_t size)
{
	return _spStream->read(p, offset, size);
}

int MemoryStream::Read(char* p, int offset, size_t size)
{
	return _spStream->read(p, offset, size);
}

__int64 MemoryStream::Seek(__int64 offset, int way)
{
	return _spStream->seekg(offset, way);
}
