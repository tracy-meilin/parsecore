#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "GPointAtom.h"


GPointAtom::GPointAtom()
{
}


GPointAtom::GPointAtom(shared_ptr<BinaryReader> spBinaryReader)
{
	this->X = spBinaryReader->ReadInt32();
	this->Y = spBinaryReader->ReadInt32();
}

GPointAtom::~GPointAtom()
{
}
