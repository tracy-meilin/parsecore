#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryWriter.h"


BinaryWriter::BinaryWriter()
{
}


BinaryWriter::BinaryWriter(shared_ptr<BaseStream> spBaseStream)
{
	_spBaseStream = spBaseStream;
}

BinaryWriter::~BinaryWriter()
{
}

size_t BinaryWriter::Write(const unsigned char* p, size_t size)
{
	if (_spBaseStream == nullptr)
		return 0;

	return _spBaseStream->Write(p, size);
}

size_t BinaryWriter::Write(const char* p, size_t size)
{
	return _spBaseStream->Write(p, size);
}

void BinaryWriter::Close()
{
	//return _spBaseStream->clo
}
