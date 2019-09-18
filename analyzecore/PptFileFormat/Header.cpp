#include "stdafx.h"
#include "InternalBitConverter.h"
#include "AbstractHeader.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "Header.h"


Header::Header()
{
}


Header::Header(shared_ptr<InputHandler> spfileHandler)
{
	_spIoHandler = spfileHandler;
	/*_spIoHandler->SetHeaderReference(shared_ptr<AbstractHeader>(this));
	ReadHeader();*/
}

Header::~Header()
{
	 
}

void Header::ReadHeader()
{
	shared_ptr<InputHandler> spInputHandler = dynamic_pointer_cast<InputHandler>(_spIoHandler);

	// Determine endian
	unsigned char tmp[2] = { 0xfe, 0xff };
	char byteArray16[2] = { 0 };
	spInputHandler->ReadPosition(byteArray16, 2, 0x1C);
	if (memcmp(byteArray16, tmp, 2) == 0)
	{
		spInputHandler->InitBitConverter(true);
	}
	else
	{
		spInputHandler->InitBitConverter(false);
	}

	unsigned __int64 lmagic = spInputHandler->ReadUInt64(0x0);
	if (lmagic != MAGIC_NUMBER)
	{
		return;
	}

	this->SetSectorShift(spInputHandler->ReadUInt16(0x1E));
	_miniSectorShift = spInputHandler->ReadUInt16();

	_noSectorsInDirectoryChain4KB = spInputHandler->ReadUInt32(0x28);
	_noSectorsInFatChain = spInputHandler->ReadUInt32();
	_directoryStartSector = spInputHandler->ReadUInt32();

	_miniSectorCutoff = spInputHandler->ReadUInt32(0x38);
	_miniFatStartSector = spInputHandler->ReadUInt32();
	_noSectorsInMiniFatChain = spInputHandler->ReadUInt32();
	_diFatStartSector = spInputHandler->ReadUInt32();
	_noSectorsInDiFatChain = spInputHandler->ReadUInt32();

}
