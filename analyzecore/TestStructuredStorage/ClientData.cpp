#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "ClientData.h"


ClientData::ClientData()
{
}


ClientData::ClientData(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->bytes = new unsigned char[this->BodySize];
	memset(this->bytes, 0, this->BodySize);
	_spBinaryReader->Read(this->bytes, this->BodySize);
}

ClientData::~ClientData()
{
	if (this->bytes != nullptr)
	{
		delete[] this->bytes;
	}
}
