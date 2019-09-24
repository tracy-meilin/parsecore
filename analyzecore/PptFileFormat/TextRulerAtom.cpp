#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "TextRulerAtom.h"


TextRulerAtom::TextRulerAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
}


TextRulerAtom::~TextRulerAtom()
{
}

//////////////////////////////////////////////////////////////////////////

TextRulerTabStop::TextRulerTabStop(shared_ptr<BinaryReader> spBinaryReader)
{
	position = spBinaryReader->ReadUInt16();
	this->TabType = (TextRulerAtomSpace::TextTabTypeEnum)spBinaryReader->ReadInt16();
}


TextRulerTabStop::~TextRulerTabStop()
{

}

//////////////////////////////////////////////////////////////////////////

TabStops::TabStops(shared_ptr<BinaryReader> spBinaryReader)
{
	this->count = spBinaryReader->ReadUInt16();
	for (unsigned long i = 0; i < count; ++i)
	{
		this->m_vecTabStops.push_back(make_shared<TextRulerTabStop>(spBinaryReader));
	}
}

TabStops::~TabStops()
{

}
