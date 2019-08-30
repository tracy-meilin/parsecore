#pragma once

class GrColorAtom
{
public:
	GrColorAtom();
	GrColorAtom(shared_ptr<BinaryReader> spBinaryReader);
	~GrColorAtom();

	bool IsSchemeColor()
	{
		return this->Index != 0xFE;
	}

public:
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Index;
};

