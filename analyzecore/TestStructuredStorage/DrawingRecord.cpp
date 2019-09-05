#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"

#include "DrawingRecord.h"


DrawingRecord::DrawingRecord()
{
}


DrawingRecord::DrawingRecord(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->csp = _spBinaryReader->ReadUInt32();
	this->spidCur = _spBinaryReader->ReadInt32();
}

DrawingRecord::~DrawingRecord()
{
}
