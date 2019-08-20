#include "stdafx.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractHeader.h"
#include "AbstractIOHandler.h"


AbstractIOHandler::AbstractIOHandler()
{
}


AbstractIOHandler::~AbstractIOHandler()
{
}

void AbstractIOHandler::InitBitConverter(bool isLittleEndian)
{
	_spBitConverter = make_shared<InternalBitConverter>(isLittleEndian);
}

void AbstractIOHandler::SetHeaderReference(shared_ptr<AbstractHeader> spHeader)
{
	_spHeader = spHeader;
}

void AbstractIOHandler::CloseStream()
{
	if (_spStream != nullptr)
	{
		_spStream->close();
	}
}
