#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDTextBody.h"
#include "NDShape.h"
#include "NDPicShape.h"


CNDPicShape::CNDPicShape(shared_ptr<ShapeContainer>& spShapeContainer)
	: CNDShape(spShapeContainer)
{
}


CNDPicShape::~CNDPicShape()
{
}

NDShapeType CNDPicShape::GetShapeType()
{
	return NDShapeType::PicShape;
}

std::shared_ptr<NDBlipFill> CNDPicShape::GetBlipFill()
{
	if (m_spShapeContainer == nullptr
		|| m_spBlipFill != nullptr)
		return m_spBlipFill;

	unsigned long indexOfPicture = 0;

	shared_ptr<ShapeOptions> spShapeOptions = m_spShapeContainer->FirstChildWithType<ShapeOptions>();
	if (spShapeOptions)
	{
		vector<shared_ptr<OptionEntry>> vecTmp = spShapeOptions->m_vecOptions;
		for (auto& ele : vecTmp)
		{
			switch (ele->pid)
			{
			case ShapeOptionsSpace::PropertyId::Pib:
				indexOfPicture = ele->op - 1;
				break;
			case ShapeOptionsSpace::PropertyId::pibName:
				//    name = Encoding.Unicode.GetString(en.opComplex);
				//    name = name.Substring(0, name.Length - 1).Replace("\0","");
				break;
			case ShapeOptionsSpace::PropertyId::pibPrintName:
				//TODO:
				break;
			default:
				break;
			}
		}
	}
	
	return m_spBlipFill;
}

std::shared_ptr<NDNVPicProperties> CNDPicShape::GetNvPicPr()
{
	if (m_spShapeContainer == nullptr
		|| m_spNvPicPr != nullptr)
		return m_spNvPicPr;

	return m_spNvPicPr;
}
