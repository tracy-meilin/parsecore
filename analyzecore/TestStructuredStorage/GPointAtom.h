#pragma once
class GPointAtom
{
public:
	GPointAtom();
	GPointAtom(shared_ptr<BinaryReader> spBinaryReader);
	~GPointAtom();

public:
	signed long X;
	signed long Y;
};

