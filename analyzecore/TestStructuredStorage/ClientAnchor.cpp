#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "ClientAnchor.h"


ClientAnchor::ClientAnchor()
{
}


ClientAnchor::ClientAnchor(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->Top = _spBinaryReader->ReadInt16();
	this->Left = _spBinaryReader->ReadInt16();
	this->Right = _spBinaryReader->ReadInt16();
	this->Bottom = _spBinaryReader->ReadInt16();
}

ClientAnchor::~ClientAnchor()
{
}
