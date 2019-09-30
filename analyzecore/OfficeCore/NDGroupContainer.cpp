#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDTextBody.h"
#include "NDShape.h"
#include "NDHeaderGrpShape.h"
#include "NDPicShape.h"
#include "NDGroupContainer.h"


CNDGroupContainer::CNDGroupContainer(shared_ptr<GroupContainer>& spGroupContainer)
	: m_spGroupContainer(spGroupContainer)
{
}


CNDGroupContainer::~CNDGroupContainer()
{
}

std::shared_ptr<CNDShape> CNDGroupContainer::GetNDFirstNvShape()
{
	Init();

	return m_spNDHeaderGrpShape;
}

std::vector<std::shared_ptr<CNDShape>> CNDGroupContainer::GetNDShapes()
{
	Init();

	return m_vecNDShapes;
}

void CNDGroupContainer::Init()
{
	if (bInit)
		return;

	vector<shared_ptr<Record>> vecChilds = m_spGroupContainer->_Child;

	// 1.获取NDFirstNvShape,并加入到shape集合
	vector<shared_ptr<Record>>::iterator itBegin = vecChilds.begin();
	if (itBegin != vecChilds.end())
	{
		shared_ptr<ShapeContainer> spShapeContainer = dynamic_pointer_cast<ShapeContainer>(*itBegin);
		if (spShapeContainer)
		{
			m_spNDHeaderGrpShape = make_shared<CNDHeaderGrpShape>(spShapeContainer);

			if (m_spNDHeaderGrpShape)
				m_vecNDShapes.push_back(m_spNDHeaderGrpShape);
		}
	}
		
	itBegin++;
	// 2.获取其余所有shape,并加入到shape集合
	for (; itBegin != vecChilds.end(); ++itBegin)
	{
		shared_ptr<ShapeContainer> spShapeContainer = dynamic_pointer_cast<ShapeContainer>(*itBegin);
		if (spShapeContainer == nullptr)
			continue;

		shared_ptr<Shape> spShape = spShapeContainer->FirstChildWithType<Shape>();
		// 获取ShapeOptions
		shared_ptr<ShapeOptions> spShapeOptions = spShapeContainer->FirstChildWithType<ShapeOptions>();

		shared_ptr<CNDShape> spNDShape = nullptr;

		do 
		{
			bool continueShape = true;

			if (spShapeContainer == nullptr)
				break;

			if (spShapeOptions->m_mapOptionsByID.find(ShapeOptionsSpace::PropertyId::Pib) != spShapeOptions->m_mapOptionsByID.end())
			{
				if (spShape && spShape->fOleShape)
				{
					// TODO: OLE Shape
				}

				if (continueShape)
				{
					spNDShape = make_shared<CNDPicShape>(spShapeContainer);
					continueShape = false;
				}
			}
		} while (false);

		if (spNDShape == nullptr)
			spNDShape = make_shared<CNDShape>(spShapeContainer);

		if (spNDShape == nullptr)
			continue;
		
		m_vecNDShapes.push_back(spNDShape);
	}
}
