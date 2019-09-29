#pragma once

class PowerPointDocument;
class PptFileFormat_API Slide
	: public RegularContainer
{
public:
	Slide();
	Slide(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~Slide();

	virtual wstring ToString(unsigned long depth) override{ return _T(""); };

	void SetPowerPointDoc(PowerPointDocument* pPPT);

	PowerPointDocument* GetPowerPointDoc(){ return m_pPPT; }

public:
	shared_ptr<SlidePersistAtom> spPersistAtom = nullptr;

private:
	PowerPointDocument* m_pPPT = nullptr;
};

