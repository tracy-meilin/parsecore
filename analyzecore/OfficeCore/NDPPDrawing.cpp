#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDShape.h"
#include "NDGroupContainer.h"
#include "NDDrawingContainer.h"
#include "NDPPDrawing.h"


CNDPPDrawing::CNDPPDrawing(shared_ptr<PPDrawing>& spPPDrawing)
	: m_spPPDrawing(spPPDrawing)
{
}


CNDPPDrawing::~CNDPPDrawing()
{
}

std::vector<std::shared_ptr<CNDDrawingContainer>>& CNDPPDrawing::GetDrawingConatiners()
{
	if (m_spPPDrawing == nullptr 
		|| m_vecDrawingContainers.size() > 0)
		return m_vecDrawingContainers;

	vector<shared_ptr<Record>> vecChilds = m_spPPDrawing->_Child;
	for (auto& ele : vecChilds)
	{
		shared_ptr<DrawingContainer> spDrawingContainer = dynamic_pointer_cast<DrawingContainer>(ele);
		if (spDrawingContainer == nullptr)
			continue;

		shared_ptr<CNDDrawingContainer> spNDDrawingContainer = make_shared<CNDDrawingContainer>(spDrawingContainer);
		if (spDrawingContainer)
			m_vecDrawingContainers.push_back(spNDDrawingContainer);
	}

	return m_vecDrawingContainers;
}
