#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "BlipStoreContainer.h"


BlipStoreContainer::BlipStoreContainer()
{
}

BlipStoreContainer::BlipStoreContainer(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{

}

BlipStoreContainer::~BlipStoreContainer()
{
}
