#include "stdafx.h"
#include "GlobalDefines.h"
#include "Utils.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RegularContainer.h"
#include "AnimationInfoContainer.h"


AnimationInfoContainer::AnimationInfoContainer()
{
}


AnimationInfoContainer::AnimationInfoContainer(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	
}

AnimationInfoContainer::~AnimationInfoContainer()
{
}

//////////////////////////////////////////////////////////////////////////

AnimationInfoAtom::AnimationInfoAtom()
{

}

AnimationInfoAtom::AnimationInfoAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	dimColor = new unsigned char[4];
	_spBinaryReader->Read(dimColor, 4);
	flags = _spBinaryReader->ReadInt16();

	fReverse = Utils::BitmaskToBool(flags, 0x1 << 0);
	fAutomatic = Utils::BitmaskToBool(flags, 0x1 << 2);
	fSound = Utils::BitmaskToBool(flags, 0x1 << 4);
	fStopSound = Utils::BitmaskToBool(flags, 0x1 << 6);
	fPlay = Utils::BitmaskToBool(flags, 0x1 << 8);
	fSynchronous = Utils::BitmaskToBool(flags, 0x1 << 10);
	fHide = Utils::BitmaskToBool(flags, 0x1 << 12);
	fAnimateBg = Utils::BitmaskToBool(flags, 0x1 << 14);

	signed short reserved = _spBinaryReader->ReadInt16();
	soundIdRef = new unsigned char[4];
	delayTime = _spBinaryReader->ReadInt32();
	orderID = _spBinaryReader->ReadInt16();
	slideCount = _spBinaryReader->ReadUInt16();
	char tmp;
	_spBinaryReader->Read(&tmp, 1);
	animBuildType = (AnimationInfoContainerSpace::AnimBuildTypeEnum)tmp;
	_spBinaryReader->Read(&animEffect, 1);
	_spBinaryReader->Read(&animEffectDirection, 1);
	_spBinaryReader->Read(&tmp, 1);
	animAfterEffect = (AnimationInfoContainerSpace::AnimAfterEffectEnum)tmp;
	_spBinaryReader->Read(&tmp, 1);
	textBuildSubEffect = (AnimationInfoContainerSpace::TextBuildSubEffectEnum)tmp;
	_spBinaryReader->Read(&oleVerb, 1);

	if (_spBinaryReader->GetPosition() != _spBinaryReader->GetLength())
	{
		_spBinaryReader->SetPosition(_spBinaryReader->GetLength());
	}
}

AnimationInfoAtom::~AnimationInfoAtom()
{

}
