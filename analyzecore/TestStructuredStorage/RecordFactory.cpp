#include "stdafx.h"
#include "Singleton.h"
#include "Common.h"
#include "GlobalDefines.h"
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
#include "UserEditAtom.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"
#include "RegularContainer.h"
#include "SlidePersistAtom.h"
#include "SlideListWithText.h"
#include "List.h"
#include "DocumentContainer.h"
#include "GPointAtom.h"
#include "GRatioAtom.h"
#include "DocumentAtom.h"
#include "BitmapBlip.h"

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
	shared_ptr<Record> spRecord = nullptr;

	switch (typeCode)
	{
	case PPT_PST_Document:
	{
		spRecord = make_shared<DocumentContainer>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_DocumentAtom:
	{
		spRecord = make_shared<DocumentAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_Environment:
	{

	}
		break;
	case PPT_PST_UserEditAtom:
	{
		spRecord = make_shared<UserEditAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_CurrentUserAtom:
	{
		spRecord = make_shared<CurrentUserAtom>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_PersistPtrIncrementalBlock:
	{
		spRecord = make_shared<PersistDirectoryAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtBitmapBlip_1E:
	case DFF_msofbtBitmapBlip_1D:
	case DFF_msofbtBitmapBlip_1F:
	case DFF_msofbtBitmapBlip_20:
	{
		spRecord = make_shared<BitmapBlip>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	break;
	default:
		break;
	}

	return spRecord;
}
