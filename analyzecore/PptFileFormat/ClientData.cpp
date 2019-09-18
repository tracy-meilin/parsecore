#include "stdafx.h"
#include "GlobalDefines.h"
#include "Singleton.h"
#include "BaseStream.h"
#include "MemoryStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "RecordFactory.h"
#include "AnimationInfoContainer.h"
#include "OEPlaceHolderAtom.h"
#include "ClientData.h"


ClientData::ClientData()
{
}


ClientData::ClientData(shared_ptr<BinaryReader> spBinaryReader, 
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
	if (spBinaryReaderTmp)
	{
		shared_ptr<Record> spRecord = RecordFactory::GetInstance()->CreateRecord(spBinaryReaderTmp);

		if (spRecord->TypeCode == 4116)
		{
			shared_ptr<AnimationInfoContainer> spAnimInfoContainer = dynamic_pointer_cast<AnimationInfoContainer>(spRecord);
			if (spAnimInfoContainer)
			{
				m_vecAnimInfoContainer.push_back(spAnimInfoContainer);

				if (spBinaryReaderTmp->GetPosition() < spBinaryReaderTmp->GetLength())
				{
					spRecord = RecordFactory::GetInstance()->CreateRecord(spBinaryReaderTmp);
					if (spRecord)
						spRecord->SiblingIdx = 1;//TODO:
				}
			}
		}

		while (true && spRecord)
		{
			switch (spRecord->TypeCode)
			{
			case 3009:
				break;
			case 3011:
			{
				shared_ptr<OEPlaceHolderAtom> spPlaceholder = dynamic_pointer_cast<OEPlaceHolderAtom>(spRecord);
				if (spPlaceholder)
				{
					if (!spPlaceholder->IsObjectPlaceholder())
					{
						spPlaceholder->PlacementId;
					}
				}
			}
				break;
			case 4116:
				break;
			case 5000:
				break;

			default:
				break;
			}

			if (spBinaryReaderTmp->GetPosition() < spBinaryReaderTmp->GetLength())
			{
				spRecord = RecordFactory::GetInstance()->CreateRecord(spBinaryReaderTmp);
			}
			else
			{
				break;
			}
		}
	}


}

ClientData::~ClientData()
{
	if (this->bytes != nullptr)
	{
		delete[] this->bytes;
	}
}
