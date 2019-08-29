#pragma once
class GRatioAtom
{
public:
	GRatioAtom();
	GRatioAtom(shared_ptr<BinaryReader> spBinaryReader);
	~GRatioAtom();

public:
	signed long Numer;
	signed long Denom;
};

