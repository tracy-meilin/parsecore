#include "stdafx.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "MemoryStream.h"
#include "VirtualStream.h"

#include "Record.h"


Record::Record()
{
}


Record::Record(shared_ptr<BinaryReader> spBinaryReader, unsigned long bodySize, unsigned long typeCode, unsigned int version, unsigned int instance)
{
	this->BodySize = bodySize;
	this->TypeCode = typeCode;
	this->Version = version;
	this->Instance = instance;
	int nRawDataSize = 0;

	if (this->BodySize <= spBinaryReader->GetLength())
	{
		RawData = new unsigned char[this->BodySize];
		spBinaryReader->Read(RawData, this->BodySize);
		nRawDataSize = this->BodySize;
	}
	else
	{
		nRawDataSize = (int)(spBinaryReader->GetLength() - spBinaryReader->GetPosition());
		RawData = new unsigned char[nRawDataSize];
		spBinaryReader->Read(RawData, nRawDataSize);
	}

	_spBinaryReader = make_shared<BinaryReader>(make_shared<MemoryStream>(RawData, nRawDataSize));
}

Record::~Record()
{
}

std::wstring Record::ToString(unsigned long depth)
{
	return _T("");
}

void Record::VerifyReadToEnd()
{
	__int64 streamPos = this->_spBinaryReader->GetPosition();
	__int64 streamLen = this->_spBinaryReader->GetLength();

	if (streamPos != streamLen)
	{
		//TODO:判断是否读取到结束
	}
}
