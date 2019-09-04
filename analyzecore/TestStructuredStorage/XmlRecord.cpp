#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "XmlRecord.h"


XmlRecord::XmlRecord()
{
}


XmlRecord::XmlRecord(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{

}

XmlRecord::~XmlRecord()
{
}
