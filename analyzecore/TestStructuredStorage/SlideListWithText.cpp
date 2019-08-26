#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "SlideListWithText.h"


SlideListWithText::SlideListWithText()
{
}

SlideListWithText::SlideListWithText(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{

}

SlideListWithText::~SlideListWithText()
{
}
