#include "stdafx.h"
#include "Singleton.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "RegularContainer.h"
#include "SlidePersisAtom.h"
#include "SlideListWithText.h"
#include "List.h"
#include "DocumentContainer.h"


DocumentContainer::DocumentContainer()
{
}

DocumentContainer::DocumentContainer(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
}


DocumentContainer::~DocumentContainer()
{
}
