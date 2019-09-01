#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "UnknownRecord.h"


UnknownRecord::UnknownRecord()
{
}


UnknownRecord::UnknownRecord(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	unsigned char* tmp = nullptr;
	if (_spBinaryReader->GetLength() - _spBinaryReader->GetPosition() >= size)
	{
		tmp = new unsigned char[size];
		_spBinaryReader->Read(tmp, size);
	}
	else
	{
		int nSize = (int)(_spBinaryReader->GetLength() - _spBinaryReader->GetPosition());
		tmp = new unsigned char[nSize];
		_spBinaryReader->Read(tmp, nSize);
	}

	if (tmp != nullptr)
	{
		delete[] tmp;
	}
}

UnknownRecord::~UnknownRecord()
{
}
