#include "stdafx.h"
#include "Singleton.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "BitmapBlip.h"
#include "Pictures.h"


Pictures::Pictures()
{
}


Pictures::Pictures(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	_spBinaryReader->SetPosition(0);

	__int64 pos;
	while (_spBinaryReader->GetPosition() < _spBinaryReader->GetLength())
	{
		pos = _spBinaryReader->GetPosition();
		shared_ptr<Record> spRecord = RecordFactory::GetInstance()->CreateRecord(_spBinaryReader);

		switch (spRecord 
			&& spRecord->TypeCode)
		{
		case 0:
			_spBinaryReader->SetPosition(_spBinaryReader->GetLength());
			break;
		case 0xF01A:
		case 0xF01B:
		case 0xF01C:
			//MetafilePictBlip mb = (MetafilePictBlip)r;
			//_pictures.insert(std::make_pair(pos, mb));
			break;
		case 0xF01D:
		case 0xF01E:
		case 0xF01F:
		case 0xF020:
		case 0xF021:
		{
			shared_ptr<BitmapBlip> spB = dynamic_pointer_cast<BitmapBlip>(spRecord);
			_pictures.insert(std::make_pair(pos, spB));
		}
			break;
		default:
			break;
		}
	}
	pos = 1;
}

Pictures::~Pictures()
{
}
