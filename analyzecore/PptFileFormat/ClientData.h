#pragma once

class PptFileFormat_API ClientData
	: public Record
{
public:
	ClientData();
	ClientData(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~ClientData();

	shared_ptr<OEPlaceHolderAtom> GetOEPlaceHolderAtom(){ return m_spPlaceholder; }

public:
	unsigned char* bytes = nullptr;
	//  public Dictionary<AnimationInfoContainer, int> animinfos = new Dictionary<AnimationInfoContainer, int>();
	// 使用vector存储单个shape的AnimationInfoContainer
	vector<shared_ptr<AnimationInfoContainer>> m_vecAnimInfoContainer;

private:
	shared_ptr<OEPlaceHolderAtom> m_spPlaceholder = nullptr;
};

