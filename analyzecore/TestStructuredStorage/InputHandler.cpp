#include "stdafx.h"
#include "GlobalDefines.h"
#include "Common.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "AbstractHeader.h"
#include "InputHandler.h"
#include "Header.h"



InputHandler::InputHandler()
{
}


InputHandler::InputHandler(const wstring& fileName)
{
	_spStream = make_shared<simple::file_istream<std::true_type>>(fileName.c_str());
}

InputHandler::InputHandler(shared_ptr<simple::file_istream<std::true_type>>& spStream)
{
	_spStream = spStream;
}

InputHandler::~InputHandler()
{
}

unsigned long InputHandler::GetIOStreamSize()
{
	return _spStream->file_length();
}

void InputHandler::ReadPosition(char* p, size_t size, long position)
{
	if (position < 0)
		return;

	_spStream->seekg(position, 0);
	_spStream->read(p, size);
}

void InputHandler::ReadPosition(unsigned char* p, size_t size, long position)
{
	if (position < 0)
		return;

	_spStream->seekg(position, 0);
	_spStream->read(p, size);
}


void InputHandler::Read(unsigned char* p, size_t size)
{
	_spStream->read(p, size);
}

// 未知offset的具体意义
void InputHandler::Read(unsigned char* p, int offset, size_t size)
{
	_spStream->read(p, size);
}

unsigned __int64 InputHandler::ReadUInt64(long position)
{
	if (position < 0)
		return 0;

	unsigned char byteArray[8] = { 0 };
	ReadPosition(byteArray, 8, position);
	return Common::bytes2T<unsigned __int64>(byteArray);
}

unsigned short InputHandler::ReadUInt16(long position)
{
	if (position < 0)
		return 0;

	unsigned char byteArray[2] = { 0 };
	ReadPosition(byteArray, 2, position);
	return Common::bytes2T<unsigned short>(byteArray);
}

unsigned short InputHandler::ReadUInt16()
{
	unsigned char byteArray[2] = { 0 };
	Read(byteArray, 2);
	return Common::bytes2T<unsigned short>(byteArray);
}

unsigned long InputHandler::ReadUInt32(long position)
{
	if (position < 0)
		return 0;

	unsigned char byteArray[4] = { 0 };
	ReadPosition(byteArray, 4, position);
	return Common::bytes2T<unsigned long>(byteArray);
}

unsigned long InputHandler::ReadUInt32()
{
	unsigned char byteArray[4] = { 0 };
	Read(byteArray, 4);
	return Common::bytes2T<unsigned long>(byteArray);
}


long InputHandler::SeekToSector(long sector)
{
	shared_ptr<Header> spHeader = dynamic_pointer_cast<Header>(_spHeader.lock());
	if (spHeader == nullptr)
		return -1;

	if (sector < 0)
		return -1;

	if (sector == -1)
	{
		_spStream->seekg(0, SEEK_SET);
		return -1;
	}

	_spStream->seekg((sector << spHeader->_sectorShift) + Common::Measures::HeaderSize, SEEK_SET);
	return -1;
}

long InputHandler::SeekToPositionInSector(long sector, long position)
{
	shared_ptr<Header> spHeader = dynamic_pointer_cast<Header>(_spHeader.lock());
	if (spHeader == nullptr)
		return -1;

	if (position < 0 || position >= spHeader->_sectorSize)
		return -1;

	if (sector == -1)
	{
		_spStream->seekg(position, SEEK_SET);
		return -1;
	}

	_spStream->seekg((sector << spHeader->_sectorShift) + Common::Measures::HeaderSize + position, SEEK_SET);
	return -1;
}
