#pragma once
class SlideListWithText 
	: public RegularContainer
{
public:
	SlideListWithText();
	SlideListWithText(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~SlideListWithText();
};

