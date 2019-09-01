#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "FileIdCluster.h"


FileIdCluster::FileIdCluster()
{
}


FileIdCluster::FileIdCluster(shared_ptr<BinaryReader> spBinaryReader)
{
	this->DrawingGroupId = spBinaryReader->ReadUInt32();
	this->DrawingGroupId = spBinaryReader->ReadUInt32();
}

FileIdCluster::~FileIdCluster()
{
}
