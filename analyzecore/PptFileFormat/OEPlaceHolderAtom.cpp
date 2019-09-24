#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "OEPlaceHolderAtom.h"


OEPlaceHolderAtom::OEPlaceHolderAtom()
{
}


OEPlaceHolderAtom::OEPlaceHolderAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->Position = _spBinaryReader->ReadInt32();
	unsigned char Tmp;
	_spBinaryReader->Read(&Tmp, 1);
	this->PlacementId = (OEPlaceHolderAtomSpace::PlaceholderEnum)Tmp;
	spBinaryReader->Read(&this->PlaceholderSize, 1);
	// Throw away additional junk
	_spBinaryReader->ReadUInt16();
}

OEPlaceHolderAtom::~OEPlaceHolderAtom()
{
}

bool OEPlaceHolderAtom::IsObjectPlaceholder()
{
	return this->PlacementId == OEPlaceHolderAtomSpace::Object;
}

std::wstring OEPlaceHolderAtom::GetPlaceholderIdToXMLValue()
{
	switch (this->PlacementId)
	{
	case OEPlaceHolderAtomSpace::MasterDate:
		return _T("dt");

	case OEPlaceHolderAtomSpace::MasterSlideNumber:
		return _T("sldNum");

	case OEPlaceHolderAtomSpace::MasterFooter:
		return _T("ftr");

	case OEPlaceHolderAtomSpace::MasterHeader:
		return _T("hdr");

	case OEPlaceHolderAtomSpace::MasterTitle:
	case OEPlaceHolderAtomSpace::Title:
		return _T("title");

	case OEPlaceHolderAtomSpace::MasterBody:
	case OEPlaceHolderAtomSpace::Body:
	case OEPlaceHolderAtomSpace::NotesBody:
	case OEPlaceHolderAtomSpace::MasterNotesBody:
		return _T("body");

	case OEPlaceHolderAtomSpace::MasterCenteredTitle:
	case OEPlaceHolderAtomSpace::CenteredTitle:
		return _T("ctrTitle");

	case OEPlaceHolderAtomSpace::MasterSubtitle:
	case OEPlaceHolderAtomSpace::Subtitle:
		return _T("subTitle");

	case OEPlaceHolderAtomSpace::ClipArt:
		return _T("clipArt");

	case OEPlaceHolderAtomSpace::Graph:
		return _T("chart");

	case OEPlaceHolderAtomSpace::OrganizationChart:
		return _T("dgm");

	case OEPlaceHolderAtomSpace::MediaClip:
		return _T("media");

	case OEPlaceHolderAtomSpace::Table:
		return _T("tbl");

	case OEPlaceHolderAtomSpace::NotesSlideImage:
	case OEPlaceHolderAtomSpace::MasterNotesSlideImage:
		return _T("sldImg");

	default:
		break;
	}

	return _T("");
}
