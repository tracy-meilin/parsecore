#include "stdafx.h"
#include "Singleton.h"
#include "Common.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractHeader.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "Header.h"
#include "AbstractFat.h"
#include "BaseStream.h"
#include "VirtualStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "CurrentUserAtom.h"

#include "RecordFactory.h"


RecordFactory::RecordFactory()
{
}


RecordFactory::~RecordFactory()
{
}

std::shared_ptr<Record> RecordFactory::CreateRecord(shared_ptr<BaseStream> spBaseStream)
{
	return CreateRecord(make_shared<BinaryReader>(spBaseStream));
}

std::shared_ptr<Record> RecordFactory::CreateRecord(shared_ptr<BinaryReader> spBinaryReader)
{
	unsigned short verAndInstance = spBinaryReader->ReadUInt16();
	// first 4 bit of field verAndInstance
	unsigned long version = verAndInstance & 0x000FU;
	// last 12 bit of field verAndInstance
	unsigned long instance = (verAndInstance & 0x000FU) >> 4;

	unsigned short typeCode = spBinaryReader->ReadUInt16();
	unsigned long size = spBinaryReader->ReadUInt32();

	bool isContainer = (version == 0xF);

	switch (typeCode)
	{
	case PPT_PST_CurrentUserAtom:
	{
		shared_ptr<CurrentUserAtom> spCurrUserAtom = make_shared<CurrentUserAtom>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	default:
		break;
	}

	return nullptr;
}
