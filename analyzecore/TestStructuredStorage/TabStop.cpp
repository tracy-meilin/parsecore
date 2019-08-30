#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "TabStop.h"


TabStop::TabStop()
{
}


TabStop::TabStop(shared_ptr<BinaryReader> spBinaryReader)
{
	this->Distance = spBinaryReader->ReadUInt16();
	this->Alignment = spBinaryReader->ReadUInt16();
}

TabStop::~TabStop()
{
}
