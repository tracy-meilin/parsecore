#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "SSlideLayoutAtom.h"


SSlideLayoutAtom::SSlideLayoutAtom()
{
}


SSlideLayoutAtom::SSlideLayoutAtom(shared_ptr<BinaryReader> spBinaryReader)
{
	signed long geom = spBinaryReader->ReadInt32();
	this->Geom = (SSlideLayoutAtomSpace::SlideLayoutType)geom;

	for (int i = 0; i < 8; ++i)
	{
		unsigned char tmp;
		spBinaryReader->Read(&tmp, 1);
		this->m_vecPlaceholderTypes.push_back((OEPlaceHolderAtomSpace::PlaceholderEnum)tmp);
	}
}

SSlideLayoutAtom::~SSlideLayoutAtom()
{
}
