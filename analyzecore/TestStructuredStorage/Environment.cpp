#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "Environment.h"


Environment::Environment()
{
}


Environment::Environment(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	for (auto& ele : _Child)
	{
		switch (ele->TypeCode)
		{
		case 0x7d5: //FontCollectionContainer
			break;
		case 0xfa3: //TextMasterStyleAtom
			//TextMasterStyleAtom a = (TextMasterStyleAtom)rec;
			break;
		case 0xfa4: //TextCFExceptionAtom
			//TextCFExceptionAtom ce = (TextCFExceptionAtom)rec;
			break;
		case 0xfa5: //TextPFExceptionAtom
			//TextPFExceptionAtom e = (TextPFExceptionAtom)rec;
			break;
		case 0xfa9: //TextSIEExceptionAtom
			break;
		case 0xfc8: //KinsokuContainer
			break;
		default:
			break;
		}
	}
}

Environment::~Environment()
{
}
