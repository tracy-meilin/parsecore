#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDShape.h"
#include "NDGroupContainer.h"
#include "NDDrawingContainer.h"


CNDDrawingContainer::CNDDrawingContainer(shared_ptr<DrawingContainer>& spDrawingContainer)
	: m_spDrawingContainer(spDrawingContainer)
{
}


CNDDrawingContainer::~CNDDrawingContainer()
{
}

std::shared_ptr<CNDGroupContainer> CNDDrawingContainer::GetGroupContainer()
{
	if (m_spDrawingContainer == nullptr 
		|| m_spNDGroupContaioner != nullptr)
		return m_spNDGroupContaioner;

	shared_ptr<GroupContainer> spGroupContainer = m_spDrawingContainer->FirstChildWithType<GroupContainer>();
	if (spGroupContainer == nullptr)
		return nullptr;

	m_spNDGroupContaioner = make_shared<CNDGroupContainer>(spGroupContainer);

	return m_spNDGroupContaioner;
}
