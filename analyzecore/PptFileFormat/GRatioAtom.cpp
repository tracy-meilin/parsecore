#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "GRatioAtom.h"


GRatioAtom::GRatioAtom()
{
}


GRatioAtom::GRatioAtom(shared_ptr<BinaryReader> spBinaryReader)
{
	this->Numer = spBinaryReader->ReadInt32();
	this->Denom = spBinaryReader->ReadInt32();
}

GRatioAtom::~GRatioAtom()
{
}
