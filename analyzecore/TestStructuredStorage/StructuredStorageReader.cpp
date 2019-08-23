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
#include "BaseStream.h"
#include "VirtualStream.h"
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

std::shared_ptr<VirtualStream> StructuredStorageReader::GetStream(wstring path)
{
	shared_ptr<DirectoryEntry> spEntry = _spDirectory->GetDirectoryEntry(path);
	if (spEntry == nullptr)
	{
		//throw new StreamNotFoundException(path);
		return nullptr;
	}

	if (spEntry->_type != Common::DirectoryEntryType::STGTY_STREAM)
	{
		//throw new WrongDirectoryEntryTypeException();
		return nullptr;
	}

	// only streams up to long.MaxValue are supported
	if (spEntry->_sizeOfStream > 9223372036854775807)		//TODO:
	{
		//throw new UnsupportedSizeException(entry.SizeOfStream.ToString());
		return nullptr;
	}

	// Determine whether this stream is a "normal stream" or a stream in the mini stream
	if (spEntry->_sizeOfStream < _spHeader->_miniSectorCutoff)
	{
		return make_shared<VirtualStream>(_spMiniFat, spEntry->_startSector, spEntry->_sizeOfStream, path);
	}
	else
	{
		return make_shared<VirtualStream>(_spFat, spEntry->_startSector, spEntry->_sizeOfStream, path);
	}
}

std::vector<std::wstring> StructuredStorageReader::GetFullNameOfAllStreamEntries()
{
	return _spDirectory->GetPathsOfAllStreamEntries();
}
