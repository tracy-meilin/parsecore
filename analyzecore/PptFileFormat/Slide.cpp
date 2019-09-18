#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "SlidePersistAtom.h"
#include "Slide.h"


Slide::Slide()
{
}

Slide::Slide(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	for (auto& ele : _Child)
	{

	}
}


Slide::~Slide()
{
}
