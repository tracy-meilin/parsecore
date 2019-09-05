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
#include "BinaryWriter.h"
#include "Record.h"
#include "CurrentUserAtom.h"
#include "UserEditAtom.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"
#include "RegularContainer.h"
#include "SlidePersistAtom.h"
#include "TabStop.h"
#include "GrColorAtom.h"
#include "CharacterRun.h"
#include "ParagraphRun.h"
#include "OutlineTextRefAtom.h"
#include "TextHeaderAtom.h"
#include "SlideListWithText.h"
#include "List.h"
#include "DocumentContainer.h"
#include "GPointAtom.h"
#include "GRatioAtom.h"
#include "DocumentAtom.h"
#include "EndDocument.h"
#include "Environment.h"
#include "UnknownRecord.h"
#include "FontEntityAtom.h"
#include "FontCollection.h"

#include "TextCFExceptionAtom.h"
#include "TextPFExceptionAtom.h"
#include "TextStyleAtom.h"
#include "TextMasterStyleAtom.h"
#include "PPDrawingGroup.h"
#include "PPDrawing.h"
#include "DrawingContainer.h"
#include "DrawingGroup.h"
#include "DrawingRecord.h"
#include "FileIdCluster.h"
#include "DrawingGroupRecord.h"
#include "BitmapBlip.h"
#include "BlipStoreContainer.h"
#include "BlipStoreEntry.h"
#include "ShapeOptions.h"
#include "ProgTags.h"
#include "ProgBinaryTag.h"
#include "StringAtom.h"
#include "ProgBinaryTagDataBlob.h"
#include "SlideHeadersFootersContainer.h"
#include "XmlRecord.h"
#include "XmlContainer.h"
#include "RoundTripContentMasterInfo12.h"
#include "RoundTripOArtTextStyles12.h"
#include "Slide.h"
#include "MainMaster.h"
#include "SSlideLayoutAtom.h"
#include "SlideAtom.h"
#include "ColorSchemeAtom.h"
#include "GroupContainer.h"
#include "ShapeContainer.h"
#include "GroupShapeRecord.h"
#include "ClientAnchor.h"
#include "ClientData.h"
#include "ClientTextbox.h"
#include "Theme.h"
#include "Handle.h"
#include "ProtectionBooleans.h"
#include "ShapeType.h"
#include "Shape.h"

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
	unsigned long instance = (verAndInstance & 0xFFF0U) >> 4;

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
	case PPT_PST_EndDocument:
	{
		spRecord = make_shared<EndDocument>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_SlideAtom:
	{
		spRecord = make_shared<SlideAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_Environment:
	{
		spRecord = make_shared<Environment>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_SlidePersistAtom:
	{
		spRecord = make_shared<SlidePersistAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_MainMaster:
	{
		spRecord = make_shared<MainMaster>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_PPDrawingGroup:
	{
		spRecord = make_shared<PPDrawingGroup>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_PPDrawing:
	{
		spRecord = make_shared<PPDrawing>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_THEME:
	{
		spRecord = make_shared<Theme>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_RoundTripContentMasterInfo12:
	{
		//TODO:LO内核没有解析
		spRecord = make_shared<RoundTripContentMasterInfo12>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_RoundTripOArtTextStyles12:
	{
		spRecord = make_shared<RoundTripOArtTextStyles12>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_List:
	{
		spRecord = make_shared<List>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_FontCollection:
	{
		spRecord = make_shared<FontCollection>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_ColorSchemeAtom:
	{
		spRecord = make_shared<ColorSchemeAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_TxMasterStyleAtom:
	{
		spRecord = make_shared<TextMasterStyleAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_TxCFStyleAtom:
	{
		spRecord = make_shared<TextCFExceptionAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_TxPFStyleAtom:
	{
		spRecord = make_shared<TextPFExceptionAtom>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_FontEntityAtom:
	{
		spRecord = make_shared<FontEntityAtom>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_CString:
	{
		spRecord = make_shared<CStringAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_HeadersFooters:
	{
		spRecord = make_shared<SlideHeadersFootersContainer>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_HeadersFootersAtom:
	{
		spRecord = make_shared<HeadersFootersAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_SlideListWithText:
	{
		spRecord = make_shared<SlideListWithText>(spBinaryReader, size, typeCode, version, instance);
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
	case PPT_PST_ProgTags:
	{
		spRecord = make_shared<ProgTags>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_ProgBinaryTag:
	{
		spRecord = make_shared<ProgBinaryTag>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_BinaryTagData:
	{
		spRecord = make_shared<ProgBinaryTagDataBlob>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_PersistPtrIncrementalBlock:
	{
		spRecord = make_shared<PersistDirectoryAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtDggContainer:
	{
		spRecord = make_shared<DrawingGroup>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case DFF_msofbtBstoreContainer:
	{
		spRecord = make_shared<BlipStoreContainer>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtDgContainer:
	{
		spRecord = make_shared<DrawingContainer>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtSpgrContainer:
	{
		spRecord = make_shared<GroupContainer>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtSpContainer:
	{
		spRecord = make_shared<ShapeContainer>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtDgg:
	{
		spRecord = make_shared<DrawingGroupRecord>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case DFF_msofbtBSE:
	{
		spRecord = make_shared<BlipStoreEntry>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case DFF_msofbtDg:
	{
		spRecord = make_shared<DrawingRecord>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtSpgr:
	{
		spRecord = make_shared<GroupShapeRecord>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtSp:
	{
		spRecord = make_shared<Shape>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtClientTextbox:
	{
		spRecord = make_shared<ClientTextbox>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtClientAnchor:
	{
		spRecord = make_shared<ClientAnchor>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtClientData:
	{
		spRecord = make_shared<ClientData>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtOPT:
	case DFF_msofbtOPT_121:
	case DFF_msofbtOPT_122:
	{
		spRecord = make_shared<ShapeOptions>(spBinaryReader, size, typeCode, version, instance);
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
	{
		spRecord = make_shared<UnknownRecord>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	}

	return spRecord;
}
