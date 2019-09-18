#include "stdafx.h"
#include "GlobalDefines.h"
#include "Utils.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "TextSpecialInfoAtom.h"




TextSIException::TextSIException(shared_ptr<BinaryReader> spBinaryReader)
{
	flags = spBinaryReader->ReadUInt32();
	spell = Utils::BitmaskToBool(flags, 0x1);
	lang = Utils::BitmaskToBool(flags, 0x1 << 1);
	altLang = Utils::BitmaskToBool(flags, 0x1 << 2);
	fPp10ext = Utils::BitmaskToBool(flags, 0x1 << 5);
	fBidi = Utils::BitmaskToBool(flags, 0x1 << 6);
	smartTag = Utils::BitmaskToBool(flags, 0x1 << 9);

	if (spell) spellInfo = spBinaryReader->ReadUInt16();
	if (lang) lid = spBinaryReader->ReadUInt16();
	if (altLang) altLid = spBinaryReader->ReadUInt16();
	if (fBidi) bidi = spBinaryReader->ReadUInt16();

	unsigned long dummy;
	if (fPp10ext) dummy = spBinaryReader->ReadUInt32();

	int nSize = spBinaryReader->GetLength() - spBinaryReader->GetPosition();
	unsigned char* smartTags = new unsigned char[nSize];
	if (smartTag) spBinaryReader->Read(smartTags, nSize);
}

TextSIException::~TextSIException()
{

}

//////////////////////////////////////////////////////////////////////////


TextSIRun::TextSIRun(shared_ptr<BinaryReader> spBinaryReader)
{
	count = spBinaryReader->ReadUInt32();
	spSI = make_shared<TextSIException>(spBinaryReader);
}


TextSIRun::~TextSIRun()
{

}

//////////////////////////////////////////////////////////////////////////

TextSpecialInfoAtom::TextSpecialInfoAtom()
{
}


TextSpecialInfoAtom::TextSpecialInfoAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	shared_ptr<TextSIRun> spRun = make_shared<TextSIRun>(spBinaryReader);
	if (spRun)
	{
		m_vecTextSIRuns.push_back(spRun);
	}
}

TextSpecialInfoAtom::~TextSpecialInfoAtom()
{
}