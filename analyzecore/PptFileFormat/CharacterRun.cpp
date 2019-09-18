#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "GrColorAtom.h"
#include "CharacterRun.h"


CharacterRun::CharacterRun()
{
}


CharacterRun::CharacterRun(shared_ptr<BinaryReader> spBinaryReader)
{
	this->Mask = (Character::CharacterMask)spBinaryReader->ReadUInt32();

	if (this->GetStyleFlagsFieldPresent())
		this->Style = (Style::StyleMask)spBinaryReader->ReadUInt16();

	if (this->GetTypefacePresent())
		this->TypefaceIdx = spBinaryReader->ReadUInt16();

	if (this->GetFEOldTypefacePresent())
		this->FEOldTypefaceIdx = spBinaryReader->ReadUInt16();

	if (this->GetANSITypefacePresent())
		this->ANSITypefaceIdx = spBinaryReader->ReadUInt16();

	if (this->GetSymbolTypefacePresent())
		this->SymbolTypefaceIdx = spBinaryReader->ReadUInt16();

	if (this->GetSizePresent())
		this->Size = spBinaryReader->ReadUInt16();

	if (this->GetColorPresent())
		this->_spColor = make_shared<GrColorAtom>(spBinaryReader);

	if (this->GetPositionPresent())
		this->Position = spBinaryReader->ReadUInt16();
}

CharacterRun::~CharacterRun()
{
}
