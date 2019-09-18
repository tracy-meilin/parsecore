#pragma once

class PptFileFormat_API ClientAnchor
	: public Record
{
public:
	ClientAnchor();
	ClientAnchor(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ClientAnchor();

public:
	signed short Top;
	signed short Left;
	signed short Right;
	signed short Bottom;
};

