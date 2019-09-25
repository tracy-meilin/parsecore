#pragma once

class PptFileFormat_API ClientTextbox
	: public Record
{
public:
	ClientTextbox();
	ClientTextbox(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~ClientTextbox();

	const shared_ptr<TextHeaderAtom>& GetTextHeaderAtom(){ return m_spTextHeaderAtom; }

	const shared_ptr<TextStyleAtom>& GetTextStyleAtom(){ return m_spTextStyleAtom; }

	const shared_ptr<MasterTextPropAtom>& GetMasterTextPropAtom(){ return m_spMasterTextPropAtom; }

	const shared_ptr<TextMasterStyleAtom>& GetDefaultMasterStyle();

public:
	unsigned char* bytes = nullptr;

private:
	shared_ptr<TextHeaderAtom> m_spTextHeaderAtom = nullptr;
	shared_ptr<TextStyleAtom> m_spTextStyleAtom = nullptr;
	shared_ptr<TextSpecialInfoAtom> m_spTextSia = nullptr;
	shared_ptr<TextRulerAtom> m_spTextRulerAtom = nullptr;
	shared_ptr<MasterTextPropAtom> m_spMasterTextPropAtom = nullptr;
	shared_ptr<TextMasterStyleAtom> m_spDefaultStyle = nullptr;
};

