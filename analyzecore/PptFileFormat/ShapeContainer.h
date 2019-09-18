#pragma once

class PptFileFormat_API ShapeContainer
	: public RegularContainer
{
public:
	ShapeContainer();
	ShapeContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ShapeContainer();

public:
	int Index;
};

