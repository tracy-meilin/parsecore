#pragma once

class PptFileFormat_API DocumentAtom
	: public Record
{
public:
	DocumentAtom();
	DocumentAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~DocumentAtom();

public:
	shared_ptr<GPointAtom> spSlideSize;
	shared_ptr<GPointAtom> spNotesSize;
	shared_ptr<GRatioAtom> spServerZoom;

	unsigned long NotesMasterPersist;
	unsigned long HandoutMasterPersist;
	unsigned short FirstSlideNum;
	Common::SlideSizeType SlideSizeType;

	bool SaveWithFonts;
	bool OmitTitlePlace;
	bool RightToLeft;
	bool ShowComments;
};

