#include "stdafx.h"
#include "NDShape.h"
#include "NDFirstNvShape.h"
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

	return m_spNDFirstNvShape;
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
			m_spNDFirstNvShape = make_shared<CNDFirstNvShape>(spShapeContainer);

			if (m_spNDFirstNvShape)
				m_vecNDShapes.push_back(m_spNDFirstNvShape);
		}
	}
		
	itBegin++;
	// 2.获取其余所有shape,并加入到shape集合
	for (; itBegin != vecChilds.end(); ++itBegin)
	{
		shared_ptr<ShapeContainer> spShapeContainer = dynamic_pointer_cast<ShapeContainer>(*itBegin);
		if (spShapeContainer == nullptr)
			continue;

		shared_ptr<CNDShape> spNDShape = make_shared<CNDShape>(spShapeContainer);
		if (spNDShape == nullptr)
			continue;
		
		m_vecNDShapes.push_back(spNDShape);
	}
}
