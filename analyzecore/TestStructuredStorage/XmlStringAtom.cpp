#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "XmlRecord.h"
#include "XmlStringAtom.h"


XmlStringAtom::XmlStringAtom()
{
}


XmlStringAtom::XmlStringAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: XmlRecord(spBinaryReader, size, typeCode, version, instance)
{
	unsigned char* bytes = new unsigned char[size];
	_spBinaryReader->Read(bytes, size);
	//TODO: ½âÎöxml
}

XmlStringAtom::~XmlStringAtom()
{
}
