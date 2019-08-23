#include "stdafx.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "VirtualStream.h"

#include "Record.h"


Record::Record()
{
}


Record::Record(shared_ptr<VirtualStream> spVirtualStream, unsigned long bodySize, unsigned long typeCode, unsigned int version, unsigned int instance)
{
	this->BodySize = bodySize;
	this->TypeCode = typeCode;
	this->Version = version;
	this->Instance = instance;

	if (this->BodySize <= spVirtualStream->GetLength())
	{
		RawData = new unsigned char[this->BodySize];
		spVirtualStream->Read(RawData, this->BodySize);
	}
	else
	{
		int nSize = (int)(spVirtualStream->GetLength() - spVirtualStream->GetPosition());
		RawData = new unsigned char[nSize];
		spVirtualStream->Read(RawData, nSize);
	}
}

Record::~Record()
{
}

std::wstring Record::ToString(unsigned long depth)
{
	return _T("");
}
