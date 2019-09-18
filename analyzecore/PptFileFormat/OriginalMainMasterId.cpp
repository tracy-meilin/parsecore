#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "OriginalMainMasterId.h"


OriginalMainMasterId::OriginalMainMasterId()
{
}


OriginalMainMasterId::OriginalMainMasterId(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->MainMasterId = _spBinaryReader->ReadUInt32();
}

OriginalMainMasterId::~OriginalMainMasterId()
{
}
