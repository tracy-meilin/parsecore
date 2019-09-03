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

signed short BinaryReader::ReadInt16()
{
	unsigned char byteArray[2] = { 0 };
	Read(byteArray, 0, 2);
	return Common::bytes2T<signed short>(byteArray);
}

unsigned long BinaryReader::ReadUInt32()
{
	unsigned char byteArray[4] = { 0 };
	Read(byteArray, 0, 4);
	return Common::bytes2T<unsigned long>(byteArray);
}

signed long BinaryReader::ReadInt32()
{
	unsigned char byteArray[4] = { 0 };
	Read(byteArray, 0, 4);
	return Common::bytes2T<signed long>(byteArray);
}

__int64 BinaryReader::ReadInt64()
{
	unsigned char byteArray[8] = { 0 };
	Read(byteArray, 8);
	return Common::bytes2T<__int64>(byteArray);
}

unsigned __int64 BinaryReader::ReadUInt64()
{
	unsigned char byteArray[8] = { 0 };
	Read(byteArray, 8);
	return Common::bytes2T<unsigned __int64>(byteArray);
}

float BinaryReader::ReadSingle()
{
	unsigned char byteArray[sizeof(float)] = { 0 };
	Read(byteArray, 0, sizeof(float));
	return Common::bytes2T<float>(byteArray);
}

double BinaryReader::ReadDouble()
{
	unsigned char byteArray[sizeof(double)] = { 0 };
	Read(byteArray, 0, sizeof(float));
	return Common::bytes2T<double>(byteArray);
}

bool BinaryReader::ReadBoolean()
{
	unsigned char tmp;
	Read(&tmp, 1);
	return Common::bytes2T<bool>(&tmp);
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

std::wstring BinaryReader::ReadUnicodeString(size_t size)
{
	if (size < 1)
		return _T("");

	wchar_t* byteArray = new wchar_t[size +1];
	memset(byteArray, 0, size);
	for (int i = 0; i < size; ++i)
	{
		byteArray[i] = ReadUInt16();
	}
	byteArray[size] = '\0';
	wstring str(byteArray);

	delete[] byteArray;
	return str;
}

__int64 BinaryReader::Seek(__int64 offset, int way)
{
	return _spBaseStream->Seek(offset, way);
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
