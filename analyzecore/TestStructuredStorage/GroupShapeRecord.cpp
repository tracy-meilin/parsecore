#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "GroupShapeRecord.h"


GroupShapeRecord::GroupShapeRecord()
{
}


GroupShapeRecord::GroupShapeRecord(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode,
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->left = max(0, _spBinaryReader->ReadInt32());
	this->top = max(0, _spBinaryReader->ReadInt32());
	this->right = max(0, _spBinaryReader->ReadInt32());
	this->bottom = max(0, _spBinaryReader->ReadInt32());
}

GroupShapeRecord::~GroupShapeRecord()
{
}
