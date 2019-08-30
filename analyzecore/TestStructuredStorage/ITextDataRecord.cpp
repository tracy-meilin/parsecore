#include "stdafx.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "GrColorAtom.h"
#include "TabStop.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "TextAtom.h"
#include "TextStyleAtom.h"
#include "TextHeaderAtom.h"
#include "ITextDataRecord.h"


ITextDataRecord::ITextDataRecord()
{
}


ITextDataRecord::~ITextDataRecord()
{
}

std::wstring ITextDataRecord::ToString(unsigned long depth)
{
	return _T("");
}
