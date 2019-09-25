#include "stdafx.h"
#include "Singleton.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "Utils.h"
#include "BaseStream.h"
#include "MemoryStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
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
#include "ClientTextbox.h"
#include "SlidePersistAtom.h"
#include "SSlideLayoutAtom.h"
#include "SlideAtom.h"
#include "Slide.h"


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

const std::shared_ptr<TextMasterStyleAtom>& ClientTextbox::GetDefaultMasterStyle()
{
	if (m_spDefaultStyle != nullptr)
		return m_spDefaultStyle;

	shared_ptr<Slide> spSlide = this->FirstAncestorWithType<Slide>();
	if (spSlide == nullptr)
		return m_spDefaultStyle;

	shared_ptr<SlideAtom> spSlideAtom = spSlide->FirstChildWithType<SlideAtom>();
	if (spSlideAtom == nullptr)
		return m_spDefaultStyle;

	if (Utils::BitmaskToBool(spSlideAtom->Flags, 0x01 << 1) && spSlideAtom->MasterId > 0)
	{

	}
}
