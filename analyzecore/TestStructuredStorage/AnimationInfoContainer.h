#pragma once
class AnimationInfoContainer 
	: public RegularContainer
{
public:
	AnimationInfoContainer();
	AnimationInfoContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~AnimationInfoContainer();
};

//////////////////////////////////////////////////////////////////////////

class AnimationInfoAtom
	: public Record
{
public:
	AnimationInfoAtom();
	AnimationInfoAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~AnimationInfoAtom();

public:
	unsigned char* dimColor = nullptr;
	signed short flags;
	unsigned char* soundIdRef = nullptr;
	signed long delayTime;
	signed short orderID;
	unsigned short slideCount;
	AnimationInfoContainerSpace::AnimBuildTypeEnum animBuildType;
	unsigned char animEffect;
	unsigned char animEffectDirection;
	AnimationInfoContainerSpace::AnimAfterEffectEnum animAfterEffect;
	AnimationInfoContainerSpace::TextBuildSubEffectEnum textBuildSubEffect;
	unsigned char oleVerb;

	bool fReverse;
	bool fAutomatic;
	bool fSound;
	bool fStopSound;
	bool fPlay;
	bool fSynchronous;
	bool fHide;
	bool fAnimateBg;
};
