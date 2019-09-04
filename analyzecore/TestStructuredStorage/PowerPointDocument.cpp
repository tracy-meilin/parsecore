#include "stdafx.h"
#include "Singleton.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"
#include "MiniFat.h"
#include "AbstractDirectoryEntry.h"
#include "DirectoryEntry.h"
#include "DirectoryTree.h"
#include "BaseStream.h"
#include "VirtualStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "StructuredStorageReader.h"
#include "CurrentUserAtom.h"
#include "UserEditAtom.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"
#include "SlidePersistAtom.h"
#include "Pictures.h"
#include "RegularContainer.h"
#include "List.h"
#include "TabStop.h"
#include "GrColorAtom.h"
#include "CharacterRun.h"
#include "ParagraphRun.h"
#include "TextHeaderAtom.h"
#include "OutlineTextRefAtom.h"
#include "SlideListWithText.h"
#include "DocumentContainer.h"
#include "Slide.h"
#include "PowerPointDocument.h"


PowerPointDocument::PowerPointDocument()
{
}


PowerPointDocument::PowerPointDocument(shared_ptr<StructuredStorageReader> spReader)
{
	this->_spCurrentUserStream = spReader->GetStream(_T("Current User"));
	shared_ptr<Record> spRecord = RecordFactory::GetInstance()->CreateRecord(_spCurrentUserStream);

	this->_spCurrentUserAtom = dynamic_pointer_cast<CurrentUserAtom>(spRecord);
	if (this->_spCurrentUserAtom == nullptr)
	{
		//TODO:
		OutputDebugString(_T("_spCurrentUserAtom is null"));
	}

	// Optional 'Pictures' stream
	vector<wstring> vecStreamEntries = spReader->GetFullNameOfAllStreamEntries();
	for (auto ele : vecStreamEntries)
	{
		if (ele == _T("\\Pictures"))
		{
			this->_spPicturesStream = spReader->GetStream(_T("Pictures"));
			this->_spPictures = make_shared<Pictures>(make_shared<BinaryReader>(this->_spPicturesStream),
				(unsigned long)this->_spPicturesStream->GetLength(), 0, 0, 0);
		}
	}

	this->_spPowerpointDocumentStream = spReader->GetStream(_T("PowerPoint Document"));

	wstring strDocSum = wstring(_T("\x5")) + _T("DocumentSummaryInformation");
	this->_spDocumentSummaryInformationStream = spReader->GetStream(strDocSum);
	ScanDocumentSummaryInformation();

	if (this->_spPowerpointDocumentStream != nullptr 
		&& this->_spCurrentUserAtom != nullptr)
	{
		this->_spPowerpointDocumentStream->Seek(this->_spCurrentUserAtom->OffsetToCurrentEdit, 0);
		shared_ptr<Record> spRecord = RecordFactory::GetInstance()->CreateRecord(_spPowerpointDocumentStream);

		this->_spLastUserEdit = dynamic_pointer_cast<UserEditAtom>(spRecord);
		if (this->_spLastUserEdit == nullptr)
		{
			//TODO:
			OutputDebugString(_T("_spUserEditAtom is null"));
		}
	}

	this->ConstructPersistObjectDirectory();

	this->IdentifyDocumentPersistObject();
	this->IdentifyMasterPersistObjects();
}

PowerPointDocument::~PowerPointDocument()
{
}

void PowerPointDocument::ScanDocumentSummaryInformation()
{
	shared_ptr<BinaryReader> spBinaryReader = make_shared<BinaryReader>(this->_spDocumentSummaryInformationStream);
	if (spBinaryReader == nullptr)
		return;

	signed short ByteOrder = spBinaryReader->ReadInt16();
	unsigned short Versioni = spBinaryReader->ReadUInt16();
	signed long SystemIdentifier = spBinaryReader->ReadInt32();
	// TODO: char to GUID
	char byteArray[16] = { 0 };
	spBinaryReader->Read(byteArray, 16);
	unsigned long NumPropertySets = spBinaryReader->ReadUInt32();
	char FMTID0[16] = { 0 };
	spBinaryReader->Read(FMTID0, 16);

	unsigned long Offset0 = spBinaryReader->ReadUInt32();
	unsigned long Offset1 = 0;
	if (NumPropertySets > 1)
	{
		char FMTID1[16] = { 0 };
		spBinaryReader->Read(FMTID1, 16);
		Offset1 = spBinaryReader->ReadUInt32();
	}

	//start of PropertySet
	unsigned long Size = spBinaryReader->ReadUInt32();
	unsigned long NumProperties = spBinaryReader->ReadUInt32();
	unsigned long id;
	unsigned long offset;
	map<unsigned long, unsigned long> Offsets;
	for (int i = 0; i < NumProperties; i++)
	{
		id = spBinaryReader->ReadUInt32();
		offset = spBinaryReader->ReadUInt32();
		Offsets.insert(make_pair(id, offset));
	}

	//start of PropertySet2
	if (Offset1 > 0)
	{
		spBinaryReader->Seek(Offset1, 0);
		Size = spBinaryReader->ReadUInt32();
		NumProperties = spBinaryReader->ReadUInt32();
		map<unsigned long, unsigned long> Offsets2;

		for (int i = 0; i < NumProperties; i++)
		{
			id = spBinaryReader->ReadUInt32();
			offset = spBinaryReader->ReadUInt32();
			Offsets2.insert(make_pair(id, offset));
		}
	}

	for(auto& ele : Offsets)
	{
		spBinaryReader->Seek(Offsets[ele.first] + Offset0, 0);

		signed short Type = spBinaryReader->ReadInt16();
		signed short Padding = spBinaryReader->ReadInt16();
		switch (Type)
		{
		case 0x0: //empty
		case 0x1:
			break;
		case 0x2: //16 bit signed int followed by zero padding to 4 bytes
			{signed short v = spBinaryReader->ReadInt16();}
			break;
		case 0x3: //32 bit signed integer
		{
			signed short v2 = spBinaryReader->ReadInt32();
			if (ele.first == 23)
			{
				//int version = BitConverter.ToInt16(BitConverter.GetBytes(v2), 2);
			}
		}
			break;
		case 0x4: //4 byte float
		{
			float v3 = spBinaryReader->ReadSingle();
		}
			break;
		case 0x5: //8 byte float
			{double v4 = spBinaryReader->ReadDouble();}
			break;
		case 0x6: //CURRENCY
			//Int64 v5 = s.ReadInt64();
			break;
		case 0x7: //DATE
			//Double v6 = s.ReadDouble();
			break;
		case 0x8: //CodePageString
		case 0x1e:
			{signed long v7 = spBinaryReader->ReadInt32();}
			//TODO: if CodePage is CP_WINUNICODE: 16 bit characters, else 8 bit characters
			//string st = Encoding.ASCII.GetString(s.ReadBytes(v7));
			break;
		case 0xA: //32 bit uint
			{unsigned long v8 = spBinaryReader->ReadUInt32();}
			break;
		case 0xB: //VARIANT_BOOL
			{bool v9 = spBinaryReader->ReadBoolean();}
			break;
		case 0xE: //DECIMAL
		{
			signed short wReserved = spBinaryReader->ReadInt16();
			char scale;
			spBinaryReader->Read(&scale, 1);
			char sign;
			spBinaryReader->Read(&sign, 1);

			signed long Hi32 = spBinaryReader->ReadInt32();
			__int64 Lo64 = spBinaryReader->ReadInt64();
		}
			break;
		case 0x10: //1 byte signed int
		{
			char tmp;
			spBinaryReader->Read(&tmp, 1);
			int v10 = (int)tmp;
		}
			break;
		case 0x11: //1 byte unsigned int
		{
			char tmp;
			spBinaryReader->Read(&tmp, 1);
			int v11 = (int)tmp;
		}
			break;
		case 0x12: //2 byte unsigned int
			{unsigned short v12 = spBinaryReader->ReadUInt16();}
			break;
		case 0x13: //4 byte unsigned int
		case 0x17:
			{unsigned long v13 = spBinaryReader->ReadUInt32();}
			break;
		case 0x14: //8 byte int
			{__int64 v14 = spBinaryReader->ReadInt64();}
			break;
		case 0x15: //8 byte unsigned int
			{unsigned __int64 v15 = spBinaryReader->ReadUInt64();}
			break;
		case 0x16: //4 byte int
			{signed long v16 = spBinaryReader->ReadInt32();}
			break;
		case 0x1f: //UnicodeString
			{wstring st2 = spBinaryReader->ReadUnicodeString(8);}
			break;
		case 0x40: //FILETIME
		{
			signed long dwLowDateTime = spBinaryReader->ReadInt32();
			signed long dwHighDateTime = spBinaryReader->ReadInt32();
		}
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// Construct the complete persist object directory by traversing all PersistDirectoryAtoms
/// from all UserEditAtoms from the last edit to the first one and adding all _entries of
/// all encountered persist directories to the resulting persist object directory.
/// 
/// When the same persist id occurs multiple times with different offsets the one from the
/// last user edit will end up in the persist object directory, overwriting earlier edits.
/// </summary>
void PowerPointDocument::ConstructPersistObjectDirectory()
{
	vector<std::shared_ptr<PersistDirectoryAtom>> pdAtom = FindLivePersistDirectoryAtoms();
	for (auto& ele : pdAtom)
	{
		for (auto& eleDirEntry : ele->PersistDirEntries)
		{
			unsigned long pid = eleDirEntry->StartPersistId;

			for (auto& eleOffsetEntry : eleDirEntry->PersistOffsetEntries )
			{
				this->_mapPersistObjectDirectory[pid] = eleOffsetEntry;
				pid++;
			}
		}
	}
}

std::vector<std::shared_ptr<PersistDirectoryAtom>> PowerPointDocument::FindLivePersistDirectoryAtoms()
{
	vector<shared_ptr<PersistDirectoryAtom>> result;
	shared_ptr<UserEditAtom> spUserEditAtom = this->_spLastUserEdit;

	while (spUserEditAtom != nullptr)
	{
		this->_spPowerpointDocumentStream->Seek(spUserEditAtom->OffsetPersistDirectory, SEEK_SET);
		shared_ptr<Record> spRecord = RecordFactory::GetInstance()->CreateRecord(_spPowerpointDocumentStream);
		shared_ptr<PersistDirectoryAtom> spPersistDirectoryAtom = dynamic_pointer_cast<PersistDirectoryAtom>(spRecord);
		if (spPersistDirectoryAtom)
		{
			result.insert(result.begin(), spPersistDirectoryAtom);
		}

		this->_spPowerpointDocumentStream->Seek(spUserEditAtom->OffsetLastEdit, SEEK_SET);

		if (spUserEditAtom->OffsetLastEdit != 0)
			spUserEditAtom = dynamic_pointer_cast<UserEditAtom>(RecordFactory::GetInstance()->CreateRecord(_spPowerpointDocumentStream));
		else
			spUserEditAtom = nullptr;
	}

	return result;
}

void PowerPointDocument::IdentifyDocumentPersistObject()
{
	this->_spDocumentRecord = this->GetPersistObject<DocumentContainer>(this->_spLastUserEdit->DocPersistIdRef);
}

void PowerPointDocument::IdentifyMasterPersistObjects()
{
	for (auto& ele : this->_spDocumentRecord->MasterPersistList)
	{
		shared_ptr<Slide> spMaster = this->GetPersistObject<Slide>(ele->PersistIdRef);
		spMaster->spPersistAtom = ele;

		//shared_ptr<MainMas>
	}
}

