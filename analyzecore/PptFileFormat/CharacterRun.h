#pragma once

class PptFileFormat_API CharacterRun
{
public:
	CharacterRun();
	CharacterRun(shared_ptr<BinaryReader> spBinaryReader);
	~CharacterRun();

	bool GetStyleFlagsFieldPresent()
	{
		return (this->Mask & Character::StyleFlagsFieldPresent) != 0;
	}

	bool GetTypefacePresent()
	{
		return (this->Mask & Character::TypefacePresent) != 0;
	}

	bool GetFEOldTypefacePresent()
	{
		return (this->Mask & Character::FEOldTypefacePresent) != 0;
	}

	bool GetANSITypefacePresent()
	{
		return (this->Mask & Character::ANSITypefacePresent) != 0;
	}

	bool GetSymbolTypefacePresent()
	{
		return (this->Mask & Character::SymbolTypefacePresent) != 0;
	}

	bool GetSizePresent()
	{
		return (this->Mask & Character::SizePresent) != 0;
	}

	bool GetPositionPresent()
	{
		return (this->Mask & Character::PositionPresent) != 0;
	}

	bool GetColorPresent()
	{
		return (this->Mask & Character::ColorPresent) != 0;
	}

public:
	unsigned long Length;
	Character::CharacterMask Mask;
	Style::StyleMask Style;
	unsigned short TypefaceIdx;
	unsigned short FEOldTypefaceIdx;
	unsigned short ANSITypefaceIdx;
	unsigned short SymbolTypefaceIdx;
	unsigned short Size;
	unsigned short Position;
	shared_ptr<GrColorAtom> _spColor = nullptr;
};

