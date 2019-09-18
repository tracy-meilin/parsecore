#include "stdafx.h"
#include "Common.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"

#include "CurrentUserAtom.h"


CurrentUserAtom::CurrentUserAtom()
{
}


CurrentUserAtom::CurrentUserAtom(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	this->Size = _spBinaryReader->ReadUInt32();
	this->HeaderToken = _spBinaryReader->ReadUInt32();

	switch (this->HeaderToken)
	{
	case 0xE391C05F: /* regular PPT file */
		break;

	case 0xF3D1C4DF: /* encrypted PPT file */
		//throw new NotSupportedException("Encryped PPT files aren't supported at this time");	default:
		break;
	default:
		break;
	}

	this->OffsetToCurrentEdit = _spBinaryReader->ReadUInt32();
	this->LengthUserName = _spBinaryReader->ReadUInt16();
	this->DocFileVersion = _spBinaryReader->ReadUInt16();
	char tmp;
	_spBinaryReader->Read(&tmp, 1);
	this->MajorVersion = tmp;
	_spBinaryReader->Read(&tmp, 1);
	this->MiniorVersion = tmp;

	//TODO£º¶ªÆú±£ÁôÊý¾Ý
	_spBinaryReader->ReadUInt16();

	//unsigned char* ansiUserNameBytes = new unsigned char[this->LengthUserName];
	//_spBinaryReader->Read(ansiUserNameBytes, this->LengthUserName);
	UserNameANSI = _spBinaryReader->ReadString(this->LengthUserName);

	this->ReleaseVersion = _spBinaryReader->ReadUInt32();

	if (_spBinaryReader->GetPosition() != _spBinaryReader->GetLength())
	{
		unsigned char* unicodeUserNameBytes = new unsigned char[this->LengthUserName * 2];
		_spBinaryReader->Read(unicodeUserNameBytes, this->LengthUserName * 2);
	}
}

CurrentUserAtom::~CurrentUserAtom()
{
}

std::wstring CurrentUserAtom::ToString(unsigned long depth)
{
	return _T("");
}
