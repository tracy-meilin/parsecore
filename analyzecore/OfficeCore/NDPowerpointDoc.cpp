#include "stdafx.h"
#include "NDShape.h"
#include "NDGroupContainer.h"
#include "NDDrawingContainer.h"
#include "NDPPDrawing.h"
#include "NDSlide.h"

#include "NDPowerpointDoc.h"

CNDPowerpointDoc::CNDPowerpointDoc()
{
}


CNDPowerpointDoc::~CNDPowerpointDoc()
{
}

bool CNDPowerpointDoc::OpenDoc(const wstring& strDocPath)
{
	shared_ptr<StructuredStorageReader> st = make_shared<StructuredStorageReader>(strDocPath);
	shared_ptr<PowerPointDocument> spPPT = make_shared<PowerPointDocument>(st);
	if (spPPT)
	{
		m_spPowerPointDoc = spPPT;
	}

	return true;
}

std::vector<std::shared_ptr<CNDSlide>>& CNDPowerpointDoc::GetSlides()
{
	if (m_spPowerPointDoc == nullptr
		|| m_vecSlides.size() > 0)
		return m_vecSlides;

	//遍历PptFileFormat组件中slide对象
	shared_ptr<DocumentContainer> spDocumentContainer = m_spPowerPointDoc->_spDocumentRecord;
	if (spDocumentContainer == nullptr)
		return m_vecSlides;

	vector<shared_ptr<SlideListWithText>> vecSlideListWithText = spDocumentContainer->AllChildrenWithType<SlideListWithText>();
	for (auto& lst : vecSlideListWithText)
	{
		if (lst->Instance == 0)			//0标识slide
		{
			vector<shared_ptr<SlidePersistAtom>> vecSlidePersistAtoms = lst->m_vecSlidePersistAtoms;
			for (auto& slideAtom : vecSlidePersistAtoms)
			{
				vector<shared_ptr<Slide>> vecSlides = m_spPowerPointDoc->m_vecSlideRecords;
				for (auto& slide : vecSlides)
				{
					if (slide->spPersistAtom == slideAtom)
					{
						//构造slide对象
						shared_ptr<CNDSlide> spNDSlide = make_shared<CNDSlide>(slide);
						m_vecSlides.push_back(spNDSlide);
					}
				}
			}
		}
	}

	return m_vecSlides;
}
