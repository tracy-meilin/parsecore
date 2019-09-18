#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "SlidePersistAtom.h"
#include "Slide.h"
#include "XmlRecord.h"
#include "XmlContainer.h"
#include "RoundTripContentMasterInfo12.h"
#include "MainMaster.h"


MainMaster::MainMaster()
{
}


MainMaster::MainMaster(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Slide(spBinaryReader, size, typeCode, version, instance)
{
	for (auto& ele : _Child)
	{
		shared_ptr<RoundTripContentMasterInfo12> sp = dynamic_pointer_cast<RoundTripContentMasterInfo12>(ele);
		if (sp)
		{
			//TODO:
		}
	}
}

MainMaster::~MainMaster()
{
}
