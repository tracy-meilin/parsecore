#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "ColorSchemeAtom.h"


ColorSchemeAtom::ColorSchemeAtom()
{
}


ColorSchemeAtom::ColorSchemeAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	//_spBinaryReader->Read(this->bytes, this->BodySize);
	this->Background = _spBinaryReader->ReadInt32();
	this->TextAndLines = _spBinaryReader->ReadInt32();
	this->Shadows = _spBinaryReader->ReadInt32();
	this->TitleText = _spBinaryReader->ReadInt32();
	this->Fills = _spBinaryReader->ReadInt32();
	this->Accent = _spBinaryReader->ReadInt32();
	this->AccentAndHyperlink = _spBinaryReader->ReadInt32();
	this->AccentAndFollowedHyperlink = _spBinaryReader->ReadInt32();
}

ColorSchemeAtom::~ColorSchemeAtom()
{
}
