#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "FontEntityAtom.h"
#include "FontCollection.h"


FontCollection::FontCollection()
{
}

FontCollection::FontCollection(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	for (auto& ele : _Child)
	{
		shared_ptr<FontEntityAtom> spFontEntityAtom = dynamic_pointer_cast<FontEntityAtom>(ele);
		if (spFontEntityAtom)
		{
			entities.push_back(spFontEntityAtom);
		}
		else
		{
			unsigned long type = spFontEntityAtom->TypeCode;
		}
	}
}

FontCollection::~FontCollection()
{
}
