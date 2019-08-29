#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "GPointAtom.h"
#include "GRatioAtom.h"
#include "BaseStream.h"

#include "Record.h"
#include "DocumentAtom.h"


DocumentAtom::DocumentAtom()
{
}

DocumentAtom::DocumentAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->spSlideSize = make_shared<GPointAtom>(_spBinaryReader);
	this->spNotesSize = make_shared<GPointAtom>(_spBinaryReader);
	this->spServerZoom = make_shared<GRatioAtom>(_spBinaryReader);

	this->NotesMasterPersist = _spBinaryReader->ReadUInt32();
	this->HandoutMasterPersist = _spBinaryReader->ReadUInt32();
	this->FirstSlideNum = _spBinaryReader->ReadUInt16();
	this->SlideSizeType = (Common::SlideSizeType)_spBinaryReader->ReadInt16();

	this->SaveWithFonts = _spBinaryReader->ReadBoolean();
	this->OmitTitlePlace = _spBinaryReader->ReadBoolean();
	this->RightToLeft = _spBinaryReader->ReadBoolean();
	this->ShowComments = _spBinaryReader->ReadBoolean();
}


DocumentAtom::~DocumentAtom()
{
}
