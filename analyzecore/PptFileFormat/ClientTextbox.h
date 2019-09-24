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

public:
	unsigned char* bytes = nullptr;

private:
	shared_ptr<TextHeaderAtom> m_spTextHeaderAtom = nullptr;
	shared_ptr<TextStyleAtom> m_spTextStyleAtom = nullptr;
	shared_ptr<TextSpecialInfoAtom> m_spTextSia = nullptr;
//	shared_ptr<TextRulerAtom>
};

