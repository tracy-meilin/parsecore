#include "stdafx.h"
#include "StringUtil.h"
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

	m_spBodyPr->lIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dxTextLeft] == nullptr 
		? 0 : m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dxTextLeft]->op;
	m_spBodyPr->tIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dyTextTop] == nullptr 
		? 0 : m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dyTextTop]->op;
	m_spBodyPr->rIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dxTextRight] == nullptr 
		? 0 : m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dxTextRight]->op;
	m_spBodyPr->bIns = m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dyTextBottom] == nullptr 
		? 0 : m_spShapeOptions->m_mapOptionsByID[ShapeOptionsSpace::dyTextBottom]->op;

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

	return m_spBodyPr;
}

std::shared_ptr<NDLstStyle> CNDTextBody::GetLstStyle()
{
	return m_spLstStyle;
}

std::vector<std::shared_ptr<NDParagraph>>& CNDTextBody::GetPs()
{
	if (m_spShapeOptions == nullptr 
		|| m_spClientTextbox == nullptr
		|| m_vecPs.size() > 0)
		return m_vecPs;

	wstring strText = _T("");

	shared_ptr<TextHeaderAtom> spTxtHeaderAtom = m_spClientTextbox->GetTextHeaderAtom();
	if (spTxtHeaderAtom)
	{
		shared_ptr<TextCharsAtom> spTextCharsAtom = dynamic_pointer_cast<TextCharsAtom>(spTxtHeaderAtom->_spTextAtom);
		if (spTxtHeaderAtom)
		{
			strText = spTextCharsAtom->Text;
		}
	}

	if (strText.empty())
		return m_vecPs;

	shared_ptr<TextStyleAtom> spTextStyleAtom = m_spClientTextbox->GetTextStyleAtom();
	shared_ptr<MasterTextPropAtom> spMasterTextPropAtom = m_spClientTextbox->GetMasterTextPropAtom();

	signed long lvl = 0;
	unsigned long idx = 0;

	vector<wstring> vecParLines = CStringUtil::ws_split(strText, _T("\r"));
	signed long internalOffset = 0;

	for (auto& ele : vecParLines)
	{
		shared_ptr<NDParagraph> spNDParagraph = make_shared<NDParagraph>();

		vector<wstring> vecRunLines = CStringUtil::ws_split(ele, _T("\v"));

		shared_ptr<ParagraphRun> spP = this->GetParagraphRun(spTextStyleAtom, idx);
		shared_ptr<MasterTextPropRun> spTp = GetMasterTextPropRun(spMasterTextPropAtom, idx);

		if (spP)
			lvl = spP->IndentLevel;

		wstring strRunText = _T("");

		//获取默认母版页样式
		shared_ptr<TextMasterStyleAtom> spDefaultStyle = m_spClientTextbox->GetDefaultMasterStyle();

		if (spP->GetAlignmentPresent())
		{
			switch (spP->Alignment)
			{
			case 0x0000: //Left
				spNDParagraph->spPPr->strAlgn = _T("l");
				break;
			case 0x0001: //Center
				spNDParagraph->spPPr->strAlgn = _T("ctr");
				break;
			case 0x0002: //Right
				spNDParagraph->spPPr->strAlgn = _T("r");
				break;
			case 0x0003: //Justify
				spNDParagraph->spPPr->strAlgn = _T("just");
				break;
			case 0x0004: //Distributed
				spNDParagraph->spPPr->strAlgn = _T("dist");
				break;
			case 0x0005: //ThaiDistributed
				spNDParagraph->spPPr->strAlgn = _T("thaiDist");
				break;
			case 0x0006: //JustifyLow
				spNDParagraph->spPPr->strAlgn = _T("justLow");
				break;
			default:
				break;
			}
		}
		else if (spDefaultStyle && spDefaultStyle->m_vecPRuns.size() > spP->IndentLevel)
		{
			if (spDefaultStyle->m_vecPRuns[spP->IndentLevel]->GetAlignmentPresent())
			{
				switch (spDefaultStyle->m_vecPRuns[spP->IndentLevel]->Alignment)
				{
				case 0x0000: //Left
					spNDParagraph->spPPr->strAlgn = _T("l");
					break;
				case 0x0001: //Center
					spNDParagraph->spPPr->strAlgn = _T("ctr");
					break;
				case 0x0002: //Right
					spNDParagraph->spPPr->strAlgn = _T("r");
					break;
				case 0x0003: //Justify
					spNDParagraph->spPPr->strAlgn = _T("just");
					break;
				case 0x0004: //Distributed
					spNDParagraph->spPPr->strAlgn = _T("dist");
					break;
				case 0x0005: //ThaiDistributed
					spNDParagraph->spPPr->strAlgn = _T("thaiDist");
					break;
				case 0x0006: //JustifyLow
					spNDParagraph->spPPr->strAlgn = _T("justLow");
					break;
				default:
					break;
				}
			}
		}

		// bullet
		if (spP->GetBulletCharPresent())
		{
			if ((spP->BulletFlags& (unsigned short)Common::HasBullet) == 0)
			{

			}
			else
			{
				if (spP->GetBulletColorPresent())
				{

				}
				else if (spP->GetBulletSizePresent())
				{

				}
				else if (spP->GetBulletFlagsFieldPresent() && (spP->BulletFlags & 0x1 << 3) > 0)
				{

				}

				if (spP->GetBulletFontPresent())
				{

				}
			}

			if (spP->GetBulletCharPresent())
			{
				spNDParagraph->spPPr->spBuChar->strChar = spP->BulletChar;
			}
			else if (!spP->GetBulletCharPresent())
			{
				spNDParagraph->spPPr->spBuChar->strChar = _T("?");
			}
		}

		//get a:r

		bool first = true;
		bool textwritten = false;
		signed long len;
		unsigned long nCharacterRunStart;
		for (auto& runLine : vecRunLines)
		{
			unsigned long offset = idx;

			if (!first)
			{
				shared_ptr<CharacterRun> spCharacterRun = GetCharacterRun(spTextStyleAtom, idx + (unsigned long)internalOffset + 1);
				if (spCharacterRun != nullptr)
				{
					//TODO:
				}

				if (runLine.length() == 0)
				{
					idx++;
					internalOffset -= 1;
				}

				internalOffset += 1;
			}

			while (idx < offset + runLine.length())
			{
				textwritten = true;
				len = runLine.length();

				shared_ptr<CharacterRun> spCharacterRun = nullptr;
				if (idx + (unsigned long)internalOffset == 0)
				{
					spCharacterRun = GetCharacterRun(spTextStyleAtom, 0);
					nCharacterRunStart = GetCharacterRunStart(spTextStyleAtom, 0);
				}
				else
				{
					spCharacterRun = GetCharacterRun(spTextStyleAtom, idx + (unsigned long)internalOffset);
					nCharacterRunStart = GetCharacterRunStart(spTextStyleAtom, idx + (unsigned long)internalOffset);
				}

				if (spCharacterRun)
				{
					len = (signed long)(nCharacterRunStart + spCharacterRun->Length - idx - internalOffset);
					if (len > runLine.size() - idx + offset) len = (signed long)(runLine.size() - idx + offset);
					if (len < 0) len = (signed long)(runLine.size() - idx + offset);
					strRunText = runLine.substr((signed long)(idx - offset), len);
				}
				else
				{
					strRunText = runLine.substr((signed long)(idx - offset));
				}

				spNDParagraph->spRun = GetR(spCharacterRun, spDefaultStyle, lvl, strRunText);

				idx += strRunText.size();
			}

			first = false;

		}		//vecRunLines

		if (!textwritten)
		{

		}
		else
		{
			// end
			//spNDParagraph->spEndParaRPr
		}

		idx += 1;

		m_vecPs.push_back(spNDParagraph);
	}			//vecParLines

	return m_vecPs;
}


std::shared_ptr<NDRun> CNDTextBody::GetR(shared_ptr<CharacterRun> spCharacterRun, 
	shared_ptr<TextMasterStyleAtom> spDefaultStyle, 
	signed long lvl, 
	wstring strRunText)
{
	if (m_spClientTextbox == nullptr)
		return nullptr;

	shared_ptr<NDRun> spRun = nullptr;

	/*shared_ptr<RegularContainer spRegularContainer = m_spClientTextbox->FirstAncestorWithType<Slide>();
	if (spRegularContainer == nullptr)
		spRegularContainer = m_spClientTextbox->FirstAncestorWithType<Note>();

	if (spRegularContainer == nullptr)
		spRegularContainer = m_spClientTextbox->FirstAncestorWithType<Handout>();*/

	spRun = make_shared<NDRun>();
	if (spCharacterRun || spDefaultStyle)
	{
		spRun->spRPr->strLang = GetLanguage();

		bool bRunExists = spCharacterRun != nullptr;

		if (bRunExists && spCharacterRun->GetSizePresent())
		{
			if (spCharacterRun->Size > 0)
			{
				spRun->spRPr->sz = spCharacterRun->Size * 100;
			}
		}
		else if (spDefaultStyle)
		{
			if (spDefaultStyle->m_vecCRuns[lvl]->GetSizePresent())
			{
				spRun->spRPr->sz = spDefaultStyle->m_vecCRuns[lvl]->Size * 100;
			}
		}

		if (bRunExists && spCharacterRun->GetStyleFlagsFieldPresent())
		{

		}
		else if (spDefaultStyle && spDefaultStyle->m_vecCRuns[lvl]->GetStyleFlagsFieldPresent())
		{

		}

		if (bRunExists && spCharacterRun->GetColorPresent())
		{

		}
		else if (spDefaultStyle)
		{
			if (spDefaultStyle->m_vecCRuns[lvl]->GetColorPresent())
			{

			}
		}

		if ((spCharacterRun->Style & Character::IsEmbossed) == Character::IsEmbossed)
		{

		}

		if (bRunExists && spCharacterRun->GetTypefacePresent())
		{

		}
		else if (spDefaultStyle && spDefaultStyle->m_vecCRuns[lvl]->GetTypefacePresent())
		{

		}
	}
	else
	{
		spRun->spRPr->strLang = GetLanguage();
	}

	// write a:t
	spRun->spT->strText = strRunText;

	return spRun;
}

std::shared_ptr<ParagraphRun> CNDTextBody::GetParagraphRun(shared_ptr<TextStyleAtom>& spTextStyleAtom, 
	unsigned long forIdex)
{
	if (spTextStyleAtom == nullptr)
		return nullptr;

	unsigned long idx = 0;
	for (auto& ele : spTextStyleAtom->m_vecPRuns)
	{
		if (forIdex < idx + ele->Length)
			return ele;

		idx += ele->Length;
	}

	return nullptr;
}

std::shared_ptr<MasterTextPropRun> CNDTextBody::GetMasterTextPropRun(shared_ptr<MasterTextPropAtom>& spMasterTextPropAtom, unsigned long forIdex)
{
	if (spMasterTextPropAtom == nullptr)
		return make_shared<MasterTextPropRun>();

	unsigned long idx = 0;
	for (auto& ele : spMasterTextPropAtom->m_vecMasterTextPropRuns)
	{
		if (forIdex < idx + ele->count)
			return ele;

		idx += ele->count;
	}

	return nullptr;
}

std::shared_ptr<CharacterRun> CNDTextBody::GetCharacterRun(shared_ptr<TextStyleAtom>& spTextStyleAtom, unsigned long forIdx)
{
	if (spTextStyleAtom == nullptr)
		return nullptr;

	unsigned long idx = 0;
	for (auto& ele : spTextStyleAtom->m_vecCRuns)
	{
		if (forIdx < idx + ele->Length)
			return ele;

		idx += ele->Length;
	}

	return nullptr;
}

unsigned long CNDTextBody::GetCharacterRunStart(shared_ptr<TextStyleAtom>& spTextStyleAtom, unsigned long forIdx)
{
	if (spTextStyleAtom == nullptr)
		return 0;

	unsigned long idx = 0;
	for (auto& ele : spTextStyleAtom->m_vecCRuns)
	{
		if (forIdx < idx + ele->Length)
			return idx;

		idx += ele->Length;
	}

	return 0;
}

std::wstring CNDTextBody::GetLanguage()
{
	shared_ptr<TextSpecialInfoAtom> spTextSia = m_spClientTextbox->GetTextSpecialInfoAtom();
	if (spTextSia == nullptr)
		return m_strLanguage;

	if (spTextSia->m_vecTextSIRuns.size() <= 0)
		return m_strLanguage;

	if (spTextSia->m_vecTextSIRuns[0]->spSI == nullptr
		|| !spTextSia->m_vecTextSIRuns[0]->spSI->lang)
		return m_strLanguage;

	switch (spTextSia->m_vecTextSIRuns[0]->spSI->lid)
	{
	case 0x0: // no language
		break;
	case 0x13: //Any Dutch language is preferred over non-Dutch languages when proofing the text
		break;
	case 0x400: //no proofing
		break;
	default:
		m_strLanguage = CLanguageUtil::GetLanguageByLCID(spTextSia->m_vecTextSIRuns[0]->spSI->lid);
			//m_strLanguage = System.Globalization.CultureInfo.GetCultureInfo(sia.Runs[0].si.lid).IetfLanguageTag;
		break;
	}

	return m_strLanguage;
}
