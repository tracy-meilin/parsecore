#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "TabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "TextCFExceptionAtom.h"
#include "TextPFExceptionAtom.h"
#include "TextStyleAtom.h"
#include "TextMasterStyleAtom.h"
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
		{
			shared_ptr<TextMasterStyleAtom> a = dynamic_pointer_cast<TextMasterStyleAtom>(ele);
		}
			break;
		case 0xfa4: //TextCFExceptionAtom
		{
			shared_ptr<TextCFExceptionAtom> a = dynamic_pointer_cast<TextCFExceptionAtom>(ele);
		}
			break;
		case 0xfa5: //TextPFExceptionAtom
		{
			shared_ptr<TextPFExceptionAtom> a = dynamic_pointer_cast<TextPFExceptionAtom>(ele);
		}
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
