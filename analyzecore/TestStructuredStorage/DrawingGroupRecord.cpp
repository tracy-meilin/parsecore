#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "FileIdCluster.h"
#include "DrawingGroupRecord.h"


DrawingGroupRecord::DrawingGroupRecord()
{
}


DrawingGroupRecord::DrawingGroupRecord(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->MaxShapeId = _spBinaryReader->ReadUInt32();
	this->IdClustersCount = _spBinaryReader->ReadUInt32() - 1;// Office saves the actual value + 1 -- flgr
	this->ShapesSavedCount = _spBinaryReader->ReadUInt32();
	this->DrawingsSavedCount = _spBinaryReader->ReadUInt32();

	for (int i = 0; i < this->IdClustersCount; ++i)
	{
		this->m_vecFileIdCluster.push_back(make_shared<FileIdCluster>(_spBinaryReader));
	}
}

DrawingGroupRecord::~DrawingGroupRecord()
{
}
