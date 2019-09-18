#pragma once

class PptFileFormat_API DrawingGroupRecord
	: public Record
{
public:
	DrawingGroupRecord();
	DrawingGroupRecord(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~DrawingGroupRecord();

public:
	unsigned long MaxShapeId;           // Maximum shape ID
	unsigned long IdClustersCount;      // Number of FileIdClusters
	unsigned long ShapesSavedCount;     // Total number of shapes saved
	unsigned long DrawingsSavedCount;   // Total number of drawings saved

	vector<shared_ptr<FileIdCluster>> m_vecFileIdCluster;
};

