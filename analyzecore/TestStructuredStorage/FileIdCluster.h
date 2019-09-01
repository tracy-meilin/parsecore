#pragma once
class FileIdCluster
{
public:
	FileIdCluster();
	FileIdCluster(shared_ptr<BinaryReader> spBinaryReader);
	~FileIdCluster();

public:
	unsigned long DrawingGroupId;
	unsigned long CSpIdCur;
};

