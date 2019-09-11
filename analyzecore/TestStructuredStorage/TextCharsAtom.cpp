#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "TextAtom.h"
#include "TextCharsAtom.h"


TextCharsAtom::TextCharsAtom()
{
}


TextCharsAtom::TextCharsAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: TextAtom(spBinaryReader, size, typeCode, version, instance, UnicodeEncoding)
{

}

TextCharsAtom::~TextCharsAtom()
{
}
