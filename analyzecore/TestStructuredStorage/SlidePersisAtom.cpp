#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "SlidePersisAtom.h"


SlidePersisAtom::SlidePersisAtom()
{
}


SlidePersisAtom::SlidePersisAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{

}

SlidePersisAtom::~SlidePersisAtom()
{
}
