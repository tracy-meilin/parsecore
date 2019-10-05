#pragma once

class PptFileFormat_API BitmapBlip
	: public Record
{
public:
	BitmapBlip();
	BitmapBlip(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);

	~BitmapBlip();

public:
	unsigned char* m_rgbUid;
	unsigned char* m_rgbUidPrimary;
	unsigned char m_bTag;
	unsigned char* m_pvBits;
	unsigned long m_nBitsLength;
};

