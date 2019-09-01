#include "stdafx.h"
#include "Singleton.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "RegularContainer.h"


RegularContainer::RegularContainer()
{
}

RegularContainer::RegularContainer(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	unsigned long readSize = 0;
	unsigned long idx = 0;

	while (readSize < this->BodySize)
	{
		shared_ptr<Record> spChild = nullptr;

		spChild = RecordFactory::GetInstance()->CreateRecord(this->_spBinaryReader);
		if (spChild == nullptr)
		{
			//TODO: 错误处理
			return;
		}

		spChild->SiblingIdx = idx;

		this->_Child.push_back(spChild);
		//TODO: 是否会引起奔溃
		spChild->SetParentRecord(shared_ptr<Record>(this));
		
		if (spChild->DoAutomaticVerifyReadToEnd())
		{
			spChild->VerifyReadToEnd();
		}

		readSize += spChild->GetTotalSize();
		idx++;
	}
}


RegularContainer::~RegularContainer()
{
}
