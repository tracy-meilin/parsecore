#pragma once

class SlideHeadersFootersContainer 
	: public RegularContainer
{
public:
	SlideHeadersFootersContainer();
	SlideHeadersFootersContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~SlideHeadersFootersContainer();
};

class HeadersFootersAtom
	: public Record
{
public:
	HeadersFootersAtom();
	HeadersFootersAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~HeadersFootersAtom();

public:
	signed short formatId;
	bool fHasDate;
	bool fHasTodayDate;
	bool fHasUserDate;
	bool fHasSlideNumber;
	bool fHasHeader;
	bool fHasFooter;
};