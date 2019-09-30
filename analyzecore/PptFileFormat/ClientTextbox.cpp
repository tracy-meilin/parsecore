#include "stdafx.h"
#include "Singleton.h"
#include "Common.h"
#include "GlobalDefines.h"
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
#include "Utils.h"
#include "BaseStream.h"
#include "VirtualStream.h"
#include "MemoryStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "StructuredStorageReader.h"
#include "CurrentUserAtom.h"
#include "UserEditAtom.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"
#include "SlidePersistAtom.h"
#include "Pictures.h"
#include "List.h"

#include "RecordFactory.h"
#include "ParagraphRunTabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "TextAtom.h"
#include "TextHeaderAtom.h"
#include "TextStyleAtom.h"
#include "TextSpecialInfoAtom.h"
#include "TextRulerAtom.h"
#include "MasterTextPropAtom.h"
#include "TextMasterStyleAtom.h"
#include "OutlineTextRefAtom.h"
#include "SlideListWithText.h"
#include "DocumentContainer.h"
#include "ClientTextbox.h"
#include "SlidePersistAtom.h"
#include "SSlideLayoutAtom.h"
#include "SlideAtom.h"
#include "Slide.h"

#include "MainMaster.h"
#include "Note.h"
#include "Handout.h"
#include "PowerPointDocument.h"


ClientTextbox::ClientTextbox()
{
}


ClientTextbox::ClientTextbox(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->bytes = new unsigned char[this->BodySize];
	memset(this->bytes, 0, this->BodySize);
	_spBinaryReader->Read(this->bytes, this->BodySize);

	shared_ptr<BinaryReader> spBinaryReaderTmp = make_shared<BinaryReader>(make_shared<MemoryStream>(this->bytes, this->BodySize));
	if (spBinaryReaderTmp == nullptr)
		return;

	shared_ptr<Record> spRecord = nullptr;
	while (spBinaryReaderTmp->GetPosition() < spBinaryReaderTmp->GetLength())
	{
		spRecord = RecordFactory::GetInstance()->CreateRecord(spBinaryReaderTmp);
		if (spRecord == nullptr)
			continue;

		switch (spRecord->TypeCode)
		{
		case 0xf9f:
			m_spTextHeaderAtom = dynamic_pointer_cast<TextHeaderAtom>(spRecord);
			break;
		case 0xfa0: //TextCharsAtom
			if (m_spTextHeaderAtom)
				m_spTextHeaderAtom->_spTextAtom = dynamic_pointer_cast<TextAtom>(spRecord);
			break;
		case 0xfa1: //StyleTextPropAtom
			m_spTextStyleAtom = dynamic_pointer_cast<TextStyleAtom>(spRecord);
			if (m_spTextStyleAtom)
				m_spTextStyleAtom->SetTextHeaderAtom(m_spTextHeaderAtom);
			break;
		case 0xfa2: //MasterTextPropAtom
			m_spMasterTextPropAtom = dynamic_pointer_cast<MasterTextPropAtom>(spRecord);
			break;
		case 0xfa6: //TextRulerAtom
			m_spTextRulerAtom = dynamic_pointer_cast<TextRulerAtom>(spRecord);
			break;
		case 0xfa8: //TextBytesAtom
		case 0xfaa: //TextSpecialInfoAtom
			m_spTextSia = dynamic_pointer_cast<TextSpecialInfoAtom>(spRecord);
			break;
		case 0xfd8: //SlideNumberMCAtom
			break;
		case 0xff7: //DateTimeMCAtom
			/*if (!phWritten && output)
			{
			_writer.WriteStartElement("p", "ph", OpenXmlNamespaces.PresentationML);
			_writer.WriteAttributeString("type", "dt");
			_writer.WriteEndElement();
			}*/
			break;
		case 0xff9: //HeaderMCAtom
			break;
		case 0xffa: //FooterMCAtom
			break;
		case 0xff8: //GenericDateMCAtom
			break;
		default:
			break;
		}
	}
}

ClientTextbox::~ClientTextbox()
{
	if (this->bytes != nullptr)
	{
		delete[] this->bytes;
	}
}

/*!
	获取默认的母版页样式
*/
const std::shared_ptr<TextMasterStyleAtom>& ClientTextbox::GetDefaultMasterStyle()
{
	if (m_spDefaultStyle != nullptr)
		return m_spDefaultStyle;

	Slide* pSlide = this->FirstAncestorWithType<Slide>();
	if (pSlide == nullptr)
		return m_spDefaultStyle;

	shared_ptr<SlideAtom> spSlideAtom = pSlide->FirstChildWithType<SlideAtom>();
	if (spSlideAtom == nullptr)
		return m_spDefaultStyle;

	if (Utils::BitmaskToBool(spSlideAtom->Flags, 0x01 << 1) && spSlideAtom->MasterId > 0)
	{
		PowerPointDocument* pPPT = pSlide->GetPowerPointDoc();
		if (pPPT == nullptr)
			return m_spDefaultStyle;

		shared_ptr<Slide> spMasterSlide = pPPT->FindMasterRecordById(spSlideAtom->MasterId);

		for (auto& ele : spMasterSlide->AllChildrenWithType<TextMasterStyleAtom>())
		{
			if (ele->Instance == (int)m_spTextHeaderAtom->TextType)
			{
				m_spDefaultStyle = ele;

				return m_spDefaultStyle;
			}
		}
	}

	return m_spDefaultStyle;
}
