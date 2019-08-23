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
#include "VirtualStream.h"
#include "Record.h"
#include "CurrentUserAtom.h"
#include "RecordFactory.h"


RecordFactory::RecordFactory()
{
}


RecordFactory::~RecordFactory()
{
}

std::shared_ptr<Record> RecordFactory::CreateRecord(shared_ptr<VirtualStream> spVirtualStream)
{
	unsigned short verAndInstance = spVirtualStream->ReadUInt16();
	// first 4 bit of field verAndInstance
	unsigned long version = verAndInstance & 0x000FU;
	// last 12 bit of field verAndInstance
	unsigned long instance = (verAndInstance & 0x000FU) >> 4;

	unsigned short typeCode = spVirtualStream->ReadUInt16();
	unsigned long size = spVirtualStream->ReadUInt32();

	bool isContainer = (version == 0xF);

	switch (typeCode)
	{
	case PPT_PST_CurrentUserAtom:
	{
		shared_ptr<CurrentUserAtom> spCurrUserAtom = make_shared<CurrentUserAtom>(spVirtualStream, size, typeCode, version, instance);
	}
		break;
	default:
		break;
	}

	return nullptr;
}
