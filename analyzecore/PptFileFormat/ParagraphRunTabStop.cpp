#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "ParagraphRunTabStop.h"


ParagraphRunTabStop::ParagraphRunTabStop()
{
}


ParagraphRunTabStop::ParagraphRunTabStop(shared_ptr<BinaryReader> spBinaryReader)
{
	this->Distance = spBinaryReader->ReadUInt16();
	this->Alignment = spBinaryReader->ReadUInt16();
}

ParagraphRunTabStop::~ParagraphRunTabStop()
{
}
