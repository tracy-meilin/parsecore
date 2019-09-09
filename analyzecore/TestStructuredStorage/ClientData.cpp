#include "stdafx.h"
#include "GlobalDefines.h"
#include "Singleton.h"
#include "SimpleBinStream.h"
#include "BaseStream.h"
#include "MemoryStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "RecordFactory.h"
#include "AnimationInfoContainer.h"
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
				//m_mapAnimInfoContainer.insert(make_pair())
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
