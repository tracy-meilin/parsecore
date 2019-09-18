#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RoundTripContentMasterId12.h"


RoundTripContentMasterId12::RoundTripContentMasterId12()
{
}


RoundTripContentMasterId12::RoundTripContentMasterId12(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->MainMasterId = _spBinaryReader->ReadUInt32();
	this->ContentMasterInstanceId = _spBinaryReader->ReadUInt32();
}

RoundTripContentMasterId12::~RoundTripContentMasterId12()
{
}
