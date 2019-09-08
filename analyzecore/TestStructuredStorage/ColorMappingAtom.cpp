#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "XmlRecord.h"
#include "XmlStringAtom.h"
#include "ColorMappingAtom.h"


ColorMappingAtom::ColorMappingAtom()
{
}


ColorMappingAtom::ColorMappingAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: XmlStringAtom(spBinaryReader, size, typeCode, version, instance)
{

}

ColorMappingAtom::~ColorMappingAtom()
{
}
