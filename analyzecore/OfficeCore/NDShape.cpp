#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDShape.h"


CNDShape::CNDShape(shared_ptr<ShapeContainer>& spShapeContainer)
	: m_spShapeContainer(spShapeContainer)
{
	if (m_spShapeContainer)
	{
		m_spShapeOptions = m_spShapeContainer->FirstChildWithType<ShapeOptions>();
	}
}


CNDShape::~CNDShape()
{
}

NDShapeType CNDShape::GetShapeType()
{
	return NDShapeType::InvalidShape;
}

std::shared_ptr<NDNVGrpShapeProperties> CNDShape::GetNvGrpSpPr()
{
	return m_spNvGrpSpPr;
}

std::shared_ptr<NDNVShapeProperties> CNDShape::GetNvSpPr()
{
	if (m_spShapeContainer == nullptr
		|| m_spNvSpPr != nullptr)
		return m_spNvSpPr;

	shared_ptr<Shape> spShape = m_spShapeContainer->FirstChildWithType<Shape>();
	if (spShape == nullptr)
		return m_spNvSpPr;

	m_spNvSpPr = make_shared<NDNVShapeProperties>();
	m_spNvSpPr->spCNvPr->spId = spShape->spid;
	m_spNvSpPr->spCNvPr->strName = _T("");

	shared_ptr<ClientData> spClientData = m_spShapeContainer->FirstChildWithType<ClientData>();
	if (spClientData)
	{
		shared_ptr<OEPlaceHolderAtom> spPlaceHolder = spClientData->GetOEPlaceHolderAtom();
		do 
		{
			if (spPlaceHolder == nullptr)
				break;

			if (!spPlaceHolder->IsObjectPlaceholder())
			{
				wstring strType = spPlaceHolder->GetPlaceholderIdToXMLValue();
				m_spNvSpPr->spNvPr->spPh->strType = strType;
			}
		} while (false);
	}

	return m_spNvSpPr;
}

std::shared_ptr<NDShapeProperties> CNDShape::GetSpPr()
{
	if (m_spShapeContainer == nullptr
		|| m_spSpPr != nullptr)
		return m_spSpPr;

	shared_ptr<Shape> spShape = m_spShapeContainer->FirstChildWithType<Shape>();
	if (spShape == nullptr)
		return m_spSpPr;

	shared_ptr<ClientAnchor> spClientAnchor = m_spShapeContainer->FirstChildWithType<ClientAnchor>();
	if (spClientAnchor
		&& spClientAnchor->Right >= spClientAnchor->Left
		&& spClientAnchor->Bottom >= spClientAnchor->Top)
	{
		m_spSpPr->spXfrm->bFlipH = spShape->fFlipH;
		m_spSpPr->spXfrm->bFlipV = spShape->fFlipV;

		m_spSpPr->spXfrm->ptOff.setX(Utils::MasterCoordToEMU(spClientAnchor->Left));
		m_spSpPr->spXfrm->ptOff.setY(Utils::MasterCoordToEMU(spClientAnchor->Top));

		m_spSpPr->spXfrm->sizeExt.setWidth(Utils::MasterCoordToEMU(spClientAnchor->Right - spClientAnchor->Left));
		m_spSpPr->spXfrm->sizeExt.setHeight(Utils::MasterCoordToEMU(spClientAnchor->Bottom - spClientAnchor->Top));
	}

	if (spShape->Instance != 0
		&& m_spShapeOptions->m_mapOptionsByID.find(ShapeOptionsSpace::pSegmentInfo) != m_spShapeOptions->m_mapOptionsByID.end())
	{
		// this means a predefined shape
		m_spSpPr->spPrstGeom->strPrst = Utils::GetPrstForShape(spShape->Instance);
	}
	else
	{
		// this means a custom shape
	}
}
