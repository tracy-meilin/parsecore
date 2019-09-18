#pragma once

class TabStop
{
public:
	TabStop();
	TabStop(shared_ptr<BinaryReader> spBinaryReader);
	~TabStop();

public:
	unsigned short Distance;
	unsigned short Alignment;
};

