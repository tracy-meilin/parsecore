#pragma once

class PptFileFormat_API ParagraphRunTabStop
{
public:
	ParagraphRunTabStop();
	ParagraphRunTabStop(shared_ptr<BinaryReader> spBinaryReader);
	~ParagraphRunTabStop();

public:
	unsigned short Distance;
	unsigned short Alignment;
};

