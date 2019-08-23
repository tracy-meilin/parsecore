#include "stdafx.h"
#include "Singleton.h"
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
#include "MiniFat.h"
#include "AbstractDirectoryEntry.h"
#include "DirectoryEntry.h"
#include "DirectoryTree.h"
#include "BaseStream.h"
#include "VirtualStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "StructuredStorageReader.h"
#include "CurrentUserAtom.h"
#include "Pictures.h"
#include "PowerPointDocument.h"


PowerPointDocument::PowerPointDocument()
{
}


PowerPointDocument::PowerPointDocument(shared_ptr<StructuredStorageReader> spReader)
{
	this->_spCurrentUserStream = spReader->GetStream(_T("Current User"));
	shared_ptr<Record> spRecord = RecordFactory::GetInstance()->CreateRecord(_spCurrentUserStream);

	this->_spCurrentUserAtom = dynamic_pointer_cast<CurrentUserAtom>(spRecord);
	if (this->_spCurrentUserAtom == nullptr)
	{
		//TODO:
		OutputDebugString(_T("_spCurrentUserAtom is null"));
	}

	// Optional 'Pictures' stream
	vector<wstring> vecStreamEntries = spReader->GetFullNameOfAllStreamEntries();
	for (auto ele : vecStreamEntries)
	{
		if (ele == _T("\\Pictures"))
		{
			this->_spPicturesStream = spReader->GetStream(_T("Pictures"));
			this->_spPictures = make_shared<Pictures>(make_shared<BinaryReader>(this->_spPicturesStream),
				(unsigned long)this->_spPicturesStream->GetLength(), 0, 0, 0);
		}
	}

	this->_spPowerpointDocumentStream = spReader->GetStream(_T("PowerPoint Document"));


}

PowerPointDocument::~PowerPointDocument()
{
}


