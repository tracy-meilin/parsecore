#include "stdafx.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "ParagraphRunTabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "Record.h"

#include "TextAtom.h"
#include "TextHeaderAtom.h"



#include "TextStyleAtom.h"


TextStyleAtom::TextStyleAtom()
{
}

TextStyleAtom::TextStyleAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{

}


TextStyleAtom::~TextStyleAtom()
{
}
