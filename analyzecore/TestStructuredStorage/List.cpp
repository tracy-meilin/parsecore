#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "List.h"


List::List()
{
}

List::List(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{

}


List::~List()
{
}
