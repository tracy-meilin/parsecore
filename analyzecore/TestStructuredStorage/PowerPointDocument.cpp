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
#include "VirtualStream.h"
#include "Record.h"
#include "RecordFactory.h"
#include "StructuredStorageReader.h"

#include "PowerPointDocument.h"


PowerPointDocument::PowerPointDocument()
{
}


PowerPointDocument::PowerPointDocument(shared_ptr<StructuredStorageReader> spReader)
{
	spCurrentUserStream = spReader->GetStream(_T("Current User"));
	shared_ptr<Record> spRecord = RecordFactory::GetInstance()->CreateRecord(spCurrentUserStream);
}

PowerPointDocument::~PowerPointDocument()
{
}


