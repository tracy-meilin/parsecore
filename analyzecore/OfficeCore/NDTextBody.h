#pragma once

// p:txBody
class CNDTextBody
{
public:
	CNDTextBody(shared_ptr<ShapeContainer>& spShapeContainer, 
		shared_ptr<ClientTextbox>& spClientTextbox);
	~CNDTextBody();

	shared_ptr<NDBodyProperties> GetBodyPr();

	shared_ptr<NDLstStyle> GetLstStyle();

	vector<shared_ptr<NDParagraph>> GetPs();

	shared_ptr<NDRun> GetR(shared_ptr<CharacterRun> spCharacterRun, 
		shared_ptr<TextMasterStyleAtom> spDefaultStyle, 
		signed long lvl, 
		wstring strRunText);

private:
	shared_ptr<ParagraphRun> GetParagraphRun(shared_ptr<TextStyleAtom>& spTextStyleAtom, unsigned long forIdex);

	shared_ptr<MasterTextPropRun> GetMasterTextPropRun(shared_ptr<MasterTextPropAtom>& spMasterTextPropAtom, unsigned long forIdex);

	shared_ptr<CharacterRun> GetCharacterRun(shared_ptr<TextStyleAtom>& spTextStyleAtom, unsigned long forIdx);

	unsigned long GetCharacterRunStart(shared_ptr<TextStyleAtom>& spTextStyleAtom, unsigned long forIdx);

	wstring GetLanguage();

private:
	shared_ptr<ClientTextbox> m_spClientTextbox = nullptr;

	shared_ptr<ShapeContainer> m_spShapeContainer = nullptr;

	shared_ptr<ShapeOptions> m_spShapeOptions = nullptr;

	//  Ù–‘
	shared_ptr<NDBodyProperties> m_spBodyPr = nullptr;

	shared_ptr<NDLstStyle> m_spLstStyle = nullptr;

	vector<shared_ptr<NDParagraph>> m_vecPs;

	wstring m_strLanguage = _T("en-US");
};

