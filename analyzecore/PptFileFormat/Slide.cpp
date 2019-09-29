#include "stdafx.h"
#include "Common.h"
#include "GlobalDefines.h"
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
#include "RegularContainer.h"

#include "StructuredStorageReader.h"
#include "CurrentUserAtom.h"
#include "UserEditAtom.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"
#include "SlidePersistAtom.h"
#include "Pictures.h"
#include "List.h"
#include "ParagraphRunTabStop.h"
#include "GPointAtom.h"
#include "GRatioAtom.h"
#include "GrColorAtom.h"
#include "CharacterRun.h"
#include "ParagraphRun.h"
#include "TextHeaderAtom.h"
#include "OutlineTextRefAtom.h"
#include "SlideListWithText.h"
#include "DocumentContainer.h"
#include "SlidePersistAtom.h"
#include "Slide.h"


#include "MainMaster.h"
#include "Note.h"
#include "Handout.h"
#include "PowerPointDocument.h"


Slide::Slide()
{
}

Slide::Slide(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	for (auto& ele : _Child)
	{

	}
}


Slide::~Slide()
{
}

void Slide::SetPowerPointDoc(PowerPointDocument* pPPT)
{
	m_pPPT = pPPT;
}
