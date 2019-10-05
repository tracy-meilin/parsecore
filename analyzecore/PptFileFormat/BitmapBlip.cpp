#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"

#include "BitmapBlip.h"


BitmapBlip::BitmapBlip()
{
}


BitmapBlip::BitmapBlip(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->m_rgbUid = new unsigned char[16];
	_spBinaryReader->Read(m_rgbUid, 16);

	if (this->Instance == 0x6E1)
	{
		this->m_rgbUidPrimary = new unsigned char[16];
		_spBinaryReader->Read(this->m_rgbUid, 16);
		_spBinaryReader->Read(&this->m_bTag, 1);
		this->m_nBitsLength = size - 33;
		this->m_pvBits = new unsigned char[this->m_nBitsLength];
		_spBinaryReader->Read(this->m_pvBits, this->m_nBitsLength);
	}
	else
	{
		this->m_rgbUidPrimary = new unsigned char[16];
		_spBinaryReader->Read(&this->m_bTag, 1);
		this->m_nBitsLength = size - 17;
		this->m_pvBits = new unsigned char[this->m_nBitsLength];
		_spBinaryReader->Read(this->m_pvBits, this->m_nBitsLength);
	}
}

BitmapBlip::~BitmapBlip()
{
}
