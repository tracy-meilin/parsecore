#pragma once

class PptFileFormat_API TextMasterStyleAtom
	: public TextStyleAtom
{
public:
	TextMasterStyleAtom();
	TextMasterStyleAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~TextMasterStyleAtom();

	shared_ptr<ParagraphRun> GetParagraphRunForIndentLevel(int level){ return m_vecPRuns[level]; };

	shared_ptr<CharacterRun> GetCharacterRunForIndentLevel(int level){ return m_vecCRuns[level]; };

public: 
	unsigned short IndentLevelCount;
	unsigned char* Bytes = nullptr;
};

