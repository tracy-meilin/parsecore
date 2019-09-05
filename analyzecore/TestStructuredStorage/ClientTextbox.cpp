#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "ClientTextbox.h"


ClientTextbox::ClientTextbox()
{
}


ClientTextbox::ClientTextbox(shared_ptr<BinaryReader> spBinaryReader, 
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

ClientTextbox::~ClientTextbox()
{
	if (this->bytes != nullptr)
	{
		delete[] this->bytes;
	}
}
