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
#include "MiniFat.h"
#include "AbstractDirectoryEntry.h"
#include "DirectoryEntry.h"
#include "DirectoryTree.h"
#include "StructuredStorageReader.h"
#include "PowerPointDocument.h"


PowerPointDocument::PowerPointDocument()
{
}


PowerPointDocument::PowerPointDocument(shared_ptr<StructuredStorageReader> spReader)
{

}

PowerPointDocument::~PowerPointDocument()
{
}
