#include "stdafx.h"
#include "Singleton.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "RegularContainer.h"
#include "SlidePersistAtom.h"
#include "SlideListWithText.h"
#include "List.h"
#include "DocumentContainer.h"
#include <algorithm>


DocumentContainer::DocumentContainer()
{
}

DocumentContainer::DocumentContainer(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	vector<shared_ptr<SlideListWithText>> vec = this->AllChildrenWithType<SlideListWithText>();
	for (auto& ele : vec)
	{
		vector<shared_ptr<SlidePersistAtom>> target;
		switch ((SlideListWithText::TextInstance)ele->Instance)
		{
		case SlideListWithText::CollectionOfMasterSlides:
			target = this->MasterPersistList;
			break;
		case SlideListWithText::CollectionOfNotesSlides:
			target = this->NotesPersistList;
			break;
		case SlideListWithText::CollectionOfSlides:
			target = this->SlidePersistList;
			break;
		default:
			break;
		}

		if (!target.empty())
		{
			for (auto& atom : ele->AllChildrenWithType<SlidePersistAtom>())
			{
				target.push_back(atom);
			}
		}

		//定义升序比较lambda函数
		auto LessSort = [](shared_ptr<SlidePersistAtom> a, shared_ptr<SlidePersistAtom> b){return a->PersistIdRef < b->PersistIdRef; };

		std::sort(MasterPersistList.begin(), MasterPersistList.end(), LessSort);
		std::sort(NotesPersistList.begin(), MasterPersistList.end(), LessSort);
		std::sort(SlidePersistList.begin(), MasterPersistList.end(), LessSort);

		this->_spDocInfoListContainer = FirstChildWithType<List>();
	}
}


DocumentContainer::~DocumentContainer()
{
}

std::shared_ptr<SlidePersistAtom> DocumentContainer::SlidePersistAtomForSlideWithIdx(unsigned long idx)
{
	for (auto& ele : this->SlidePersistList)
	{
		// idx is zero-based, psr-reference is one-based
		if (ele->PersistIdRef == idx + 1)
			return ele;
	}

	return nullptr;
}
