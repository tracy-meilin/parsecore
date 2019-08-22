#include "stdafx.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"
#include "AbstractDirectoryEntry.h"
#include "DirectoryEntry.h"
#include "DirectoryTree.h"
#include "MiniFat.h"
#include "StructuredStorageReader.h"


StructuredStorageReader::StructuredStorageReader()
{
}


StructuredStorageReader::StructuredStorageReader(const wstring& fileName)
{
	_spFileHandler = make_shared<InputHandler>(fileName);

	//////////////////////////////////////////////////////////////////////////
	_spHeader = make_shared<Header>(_spFileHandler);
	// 单独提取出来，避免弱引用、强引用问题导致内存释放奔溃
	_spFileHandler->SetHeaderReference(_spHeader);
	_spHeader->ReadHeader();
	//////////////////////////////////////////////////////////////////////////

	_spFat = make_shared<Fat>(_spHeader, _spFileHandler);
	_spDirectory = make_shared<DirectoryTree>(_spFat, _spHeader, _spFileHandler);
	_spMiniFat = make_shared<MiniFat>(_spFat, _spHeader, _spFileHandler, _spDirectory->GetMiniStreamStart(), _spDirectory->GetSizeOfMiniStream());
}

StructuredStorageReader::~StructuredStorageReader()
{

}
