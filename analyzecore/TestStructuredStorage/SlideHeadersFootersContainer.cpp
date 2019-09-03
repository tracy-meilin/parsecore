#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "SlideHeadersFootersContainer.h"


SlideHeadersFootersContainer::SlideHeadersFootersContainer()
{
}


SlideHeadersFootersContainer::SlideHeadersFootersContainer(shared_ptr<BinaryReader> spBinaryReader, 
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

SlideHeadersFootersContainer::~SlideHeadersFootersContainer()
{
}

//////////////////////////////////////////////////////////////////////////

HeadersFootersAtom::HeadersFootersAtom()
{

}

HeadersFootersAtom::HeadersFootersAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	:Record(spBinaryReader, size, typeCode, version, instance)
{
	formatId = _spBinaryReader->ReadInt16();

	signed short mask = _spBinaryReader->ReadInt16();
	fHasDate = ((mask & (1)) != 0);
	fHasTodayDate = ((mask & (1 << 1)) != 0);
	fHasUserDate = ((mask & (1 << 2)) != 0);
	fHasSlideNumber = ((mask & (1 << 3)) != 0);
	fHasHeader = ((mask & (1 << 4)) != 0);
	fHasFooter = ((mask & (1 << 5)) != 0);
}

HeadersFootersAtom::~HeadersFootersAtom()
{

}
