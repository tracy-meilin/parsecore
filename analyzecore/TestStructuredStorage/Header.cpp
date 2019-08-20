#include "stdafx.h"
#include "SimpleBinStream.h"
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
	_spIoHandler->SetHeaderReference(shared_ptr<AbstractHeader>(this));
	ReadHeader();
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
}
