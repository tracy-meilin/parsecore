#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "XmlRecord.h"
#include "XmlContainer.h"
#include "Theme.h"


Theme::Theme()
{
}


Theme::Theme(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: XmlContainer(spBinaryReader, size, typeCode, version, instance)
{

}

Theme::~Theme()
{
}
