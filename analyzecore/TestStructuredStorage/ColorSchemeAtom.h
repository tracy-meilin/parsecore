#pragma once

class ColorSchemeAtom 
	: public Record
{
public:
	ColorSchemeAtom();
	ColorSchemeAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~ColorSchemeAtom();

public:
	unsigned char* bytes = nullptr;
	signed long Background;
	signed long TextAndLines;
	signed long Shadows;
	signed long TitleText;
	signed long Fills;
	signed long Accent;
	signed long AccentAndHyperlink;
	signed long AccentAndFollowedHyperlink;
};

