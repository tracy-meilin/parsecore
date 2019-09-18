#include "stdafx.h"
#include "Singleton.h"
#include "BaseStream.h"
#include "MemoryStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "ClientTextbox.h"


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
		case 0xfa0: //TextCharsAtom
		case 0xfa1: //TextRunStyleAtom
		case 0xfa6: //TextRulerAtom
		case 0xfa8: //TextBytesAtom
		case 0xfaa: //TextSpecialInfoAtom
		case 0xfa2: //MasterTextPropAtom
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
