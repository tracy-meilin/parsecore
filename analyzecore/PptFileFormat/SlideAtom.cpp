#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "SSlideLayoutAtom.h"
#include "SlideAtom.h"


SlideAtom::SlideAtom()
{
}


SlideAtom::SlideAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->_spLayout = make_shared<SSlideLayoutAtom>(this->_spBinaryReader);
	this->MasterId = _spBinaryReader->ReadUInt32();
	this->NotesId = _spBinaryReader->ReadInt32();
	this->Flags = _spBinaryReader->ReadUInt16();
	_spBinaryReader->ReadUInt16(); // Throw away undocumented data
}

SlideAtom::~SlideAtom()
{
}
