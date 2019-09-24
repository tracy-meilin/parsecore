#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDTextBody.h"


CNDTextBody::CNDTextBody(shared_ptr<ShapeContainer>& spShapeContainer, 
	shared_ptr<ClientTextbox>& spClientTextbox)
	: m_spShapeContainer(spShapeContainer)
	, m_spClientTextbox(spClientTextbox)
{
	if (m_spShapeContainer)
	{
		m_spShapeOptions = m_spShapeContainer->FirstChildWithType<ShapeOptions>();
	}
}

CNDTextBody::~CNDTextBody()
{

}

std::shared_ptr<NDBodyProperties> CNDTextBody::GetBodyPr()
{
	if (m_spShapeOptions == nullptr
		|| m_spBodyPr != nullptr)
		return m_spBodyPr;

	m_spBodyPr = make_shared<NDBodyProperties>();

	m_spBodyPr->lIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dxTextLeft]->op;
	m_spBodyPr->tIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dyTextTop]->op;
	m_spBodyPr->rIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dxTextRight]->op;
	m_spBodyPr->bIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dyTextBottom]->op;

	if (m_spShapeOptions->m_mapOptionsByID.find(ShapeOptionsSpace::WrapText)
		!= m_spShapeOptions->m_mapOptionsByID.end())
	{
		unsigned long tmp = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::WrapText]->op;
		switch (tmp)
		{
		case 0: //square
			m_spBodyPr->strWrap = _T("square");
			break;
		case 1: //by points
			break; //TODO
		case 2: //none
			m_spBodyPr->strWrap = _T("none");
			break;
		case 3: //top bottom
		case 4: //through
		default:
			break; //TODO
		}
	}

	if (m_spShapeOptions->m_mapOptionsByID.find(ShapeOptionsSpace::anchorText)
		!= m_spShapeOptions->m_mapOptionsByID.end())
	{
		unsigned long tmp = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::anchorText]->op;
		switch (tmp)
		{
		case 0: //Top
			m_spBodyPr->strAnchor = _T("t");
			break;
		case 1: //Middle
			m_spBodyPr->strAnchor = _T("ctr");
			break;
		case 2: //Bottom
			m_spBodyPr->strAnchor = _T("b");
			break;
		case 3: //TopCentered
			m_spBodyPr->strAnchor = _T("t");
			m_spBodyPr->bAnchorCtrl = true;
			break;
		case 4: //MiddleCentered
			m_spBodyPr->strAnchor = _T("ctr");
			m_spBodyPr->bAnchorCtrl = true;
			break;
		case 5: //BottomCentered
			m_spBodyPr->strAnchor = _T("b");
			m_spBodyPr->bAnchorCtrl = true;
			break;
		case 6: //TopBaseline
		case 7: //BottomBaseline
		case 8: //TopCenteredBaseline
		case 9: //BottomCenteredBaseline
			//TODO
			break;
		}
	}
}

std::shared_ptr<NDLstStyle> CNDTextBody::GetLstStyle()
{
	return m_spLstStyle;
}

std::vector<std::shared_ptr<NDParagraph>> CNDTextBody::GetPs()
{
	if (m_spShapeOptions == nullptr
		|| m_vecPs.size() > 0)
		return m_vecPs;


}
