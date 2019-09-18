#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "ProgBinaryTagDataBlob.h"


ProgBinaryTagDataBlob::ProgBinaryTagDataBlob()
{
}


ProgBinaryTagDataBlob::ProgBinaryTagDataBlob(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	for (auto& ele : _Child)
	{
		switch (ele->TypeCode)
		{
		case 0x2b00: //HashCode10Atom
			break;
		case 0x2b02: //BuildListContainer
			break;
		case 0x36b1: //DocToolbarStates10Atom
			break;
		case 0x40d: //GridSpacing10Atom
			break;
		case 0x7f8: //BlipCollection9
			break;
		case 0x2eeb: //SlideTime10Atom
			break;
		case 0xf144: //ExtTimeNodeContainer
			break;
		case 0xfad: //TextMasterStyle9Atom
			break;
		default:
			break;
		}
	}
}

ProgBinaryTagDataBlob::~ProgBinaryTagDataBlob()
{
}
