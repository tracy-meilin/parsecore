#include "stdafx.h"
#include "Common.h"
#include "BaseStream.h"
#include "BinaryReader.h"


BinaryReader::BinaryReader()
{
}


BinaryReader::BinaryReader(shared_ptr<BaseStream> spBaseStream)
{
	_spBaseStream = spBaseStream;
}

BinaryReader::~BinaryReader()
{
}

unsigned short BinaryReader::ReadUInt16()
{
	unsigned char byteArray[2] = { 0 };
	Read(byteArray, 0, 2);
	return Common::bytes2T<unsigned short>(byteArray);
}

unsigned long BinaryReader::ReadUInt32()
{
	unsigned char byteArray[4] = { 0 };
	Read(byteArray, 0, 4);
	return Common::bytes2T<unsigned long>(byteArray);
}

int BinaryReader::Read(unsigned char* p, int offset, size_t size)
{
	return _spBaseStream->Read(p, offset, size);
}

int BinaryReader::Read(char* p, int offset, size_t size)
{
	return _spBaseStream->Read(p, offset, size);
}

int BinaryReader::Read(unsigned char* p, size_t size)
{
	return _spBaseStream->Read(p, 0, size);
}

int BinaryReader::Read(char* p, size_t size)
{
	return _spBaseStream->Read(p, 0, size);
}

std::string BinaryReader::ReadString(size_t size)
{
	if (size < 1)
		return "";

	char* byteArray = new char[size];
	Read(byteArray, size);

	string str(byteArray);

	delete[] byteArray;
	return str;
}

__int64 BinaryReader::GetPosition()
{
	return _spBaseStream->GetPosition();
}

void BinaryReader::SetPosition(__int64 position)
{
	return _spBaseStream->SetPosition(position);
}

__int64 BinaryReader::GetLength()
{
	return _spBaseStream->GetLength();
}
