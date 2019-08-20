#include "stdafx.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "StructuredStorageReader.h"


StructuredStorageReader::StructuredStorageReader()
{
}


StructuredStorageReader::StructuredStorageReader(const wstring& fileName)
{
	_spFileHandler = make_shared<InputHandler>(fileName);
	_spHeader = make_shared<Header>(_spFileHandler);
}

StructuredStorageReader::~StructuredStorageReader()
{
}
