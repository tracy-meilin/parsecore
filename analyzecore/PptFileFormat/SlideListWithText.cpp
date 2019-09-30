#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "TextAtom.h"
#include "ParagraphRunTabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "SlidePersistAtom.h"
#include "TextHeaderAtom.h"
#include "OutlineTextRefAtom.h"
#include "Slide.h"
#include "SlideListWithText.h"


SlideListWithText::SlideListWithText()
{
}

SlideListWithText::SlideListWithText(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	shared_ptr<SlidePersistAtom> spCurSpAtom = nullptr;
	shared_ptr<TextHeaderAtom> spCurThAtom = nullptr;

	for (auto& ele : _Child)
	{
		shared_ptr<SlidePersistAtom> spSpAtom = dynamic_pointer_cast<SlidePersistAtom>(ele);
		shared_ptr<TextHeaderAtom> spThAtom = dynamic_pointer_cast<TextHeaderAtom>(ele);
		shared_ptr<ITextDataRecord> spTdRecord = dynamic_pointer_cast<ITextDataRecord>(ele);

		if (spSpAtom != nullptr)
		{
			spCurSpAtom = spSpAtom;
			this->m_vecSlidePersistAtoms.push_back(spSpAtom);
		}
		else if (spThAtom != nullptr)
		{
			spCurThAtom = spThAtom;
			auto& ele = m_mapSlideToPlaceholderTextHeaders.find(spCurSpAtom);
			if (ele == m_mapSlideToPlaceholderTextHeaders.end())
			{
				vector<shared_ptr<TextHeaderAtom>> vecTextHeaderAtom;
				m_mapSlideToPlaceholderTextHeaders.insert(make_pair(spCurSpAtom, vecTextHeaderAtom));
			}

			m_mapSlideToPlaceholderTextHeaders[spCurSpAtom].push_back(spThAtom);
		}

	}
}

SlideListWithText::~SlideListWithText()
{
}

std::shared_ptr<TextHeaderAtom> SlideListWithText::FindTextHeaderForOutlineTextRef(shared_ptr<OutlineTextRefAtom> spAtom)
{
	Slide* pSlide = spAtom->FirstAncestorWithType<Slide>();
	if (pSlide == nullptr)
	{
		//TODO£º
		return nullptr;
	}

	vector<shared_ptr<TextHeaderAtom>> thAtoms = this->m_mapSlideToPlaceholderTextHeaders[pSlide->spPersistAtom];
	return thAtoms[spAtom->Index];
}
