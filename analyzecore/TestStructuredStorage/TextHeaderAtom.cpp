#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "TextAtom.h"
#include "TabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "TextStyleAtom.h"


#include "TextHeaderAtom.h"

TextHeaderAtom::TextHeaderAtom()
{
}

TextHeaderAtom::TextHeaderAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->TextType = (Common::TextType)_spBinaryReader->ReadUInt32();
}

TextHeaderAtom::~TextHeaderAtom()
{
}

void TextHeaderAtom::HandleTextDataRecord(shared_ptr<ITextDataRecord> spTdRecord)
{
	spTdRecord->_spTextHeaderAtom = shared_ptr<TextHeaderAtom>(this);
	
	shared_ptr<TextAtom> spTextAtom = dynamic_pointer_cast<TextAtom>(spTdRecord);
}
