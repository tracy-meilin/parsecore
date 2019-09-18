#pragma once

class PptFileFormat_API FileIdCluster
{
public:
	FileIdCluster();
	FileIdCluster(shared_ptr<BinaryReader> spBinaryReader);
	~FileIdCluster();

public:
	unsigned long DrawingGroupId;
	unsigned long CSpIdCur;
};

