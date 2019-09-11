#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "FooterMCAtom.h"


FooterMCAtom::FooterMCAtom()
{
}


FooterMCAtom::FooterMCAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	Position = spBinaryReader->ReadInt32();
}

FooterMCAtom::~FooterMCAtom()
{
}

//////////////////////////////////////////////////////////////////////////

DateTimeMCAtom::DateTimeMCAtom()
{
}


DateTimeMCAtom::DateTimeMCAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	Position = spBinaryReader->ReadInt32();
	spBinaryReader->Read(&index, 1);
}

DateTimeMCAtom::~DateTimeMCAtom()
{
}

//////////////////////////////////////////////////////////////////////////

HeaderMCAtom::HeaderMCAtom()
{
}


HeaderMCAtom::HeaderMCAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	Position = spBinaryReader->ReadInt32();
}

HeaderMCAtom::~HeaderMCAtom()
{
}

//////////////////////////////////////////////////////////////////////////

SlideNumberMCAtom::SlideNumberMCAtom()
{
}


SlideNumberMCAtom::SlideNumberMCAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	Position = spBinaryReader->ReadInt32();
}

SlideNumberMCAtom::~SlideNumberMCAtom()
{
}

//////////////////////////////////////////////////////////////////////////

GenericDateMCAtom::GenericDateMCAtom()
{
}


GenericDateMCAtom::GenericDateMCAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	Position = spBinaryReader->ReadInt32();
}

GenericDateMCAtom::~GenericDateMCAtom()
{
}

