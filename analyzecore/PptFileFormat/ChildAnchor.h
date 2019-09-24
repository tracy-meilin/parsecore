#pragma once

class PptFileFormat_API ChildAnchor 
	: public Record
{
public:
	ChildAnchor();
	ChildAnchor(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ChildAnchor();

public:
	signed short Top;
	signed short Left;
	signed short Right;
	signed short Bottom;
};

