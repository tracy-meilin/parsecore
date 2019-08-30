#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "GrColorAtom.h"


GrColorAtom::GrColorAtom()
{
}


GrColorAtom::GrColorAtom(shared_ptr<BinaryReader> spBinaryReader)
{
	spBinaryReader->Read(&Red, 1);
	spBinaryReader->Read(&Green, 1);
	spBinaryReader->Read(&Blue, 1);
	spBinaryReader->Read(&Index, 1);
}

GrColorAtom::~GrColorAtom()
{
}
