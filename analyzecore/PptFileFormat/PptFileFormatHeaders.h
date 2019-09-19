#pragma once

//包含该有的头文件，而不应该由调用者去包含
#include <map>
#include <string>
#include <vector>

using namespace std;

#include "../PptFileFormat/Common.h"
#include "../PptFileFormat/GlobalDefines.h"
#include "../PptFileFormat/InternalBitConverter.h"
#include "../PptFileFormat/AbstractIOHandler.h"
#include "../PptFileFormat/InputHandler.h"
#include "../PptFileFormat/AbstractHeader.h"
#include "../PptFileFormat/Header.h"
#include "../PptFileFormat/AbstractFat.h"
#include "../PptFileFormat/Fat.h"
#include "../PptFileFormat/AbstractDirectoryEntry.h"
#include "../PptFileFormat/DirectoryEntry.h"
#include "../PptFileFormat/DirectoryTree.h"
#include "../PptFileFormat/MiniFat.h"
#include "../PptFileFormat/BaseStream.h"
#include "../PptFileFormat/VirtualStream.h"
#include "../PptFileFormat/StructuredStorageReader.h"

#include "../PptFileFormat/BinaryReader.h"
#include "../PptFileFormat/Record.h"
#include "../PptFileFormat/CurrentUserAtom.h"
#include "../PptFileFormat/UserEditAtom.h"
#include "../PptFileFormat/Pictures.h"
#include "../PptFileFormat/PersistDirectoryEntry.h"
#include "../PptFileFormat/PersistDirectoryAtom.h"
#include "../PptFileFormat/SlidePersistAtom.h"
#include "../PptFileFormat/RegularContainer.h"
#include "../PptFileFormat/List.h"
#include "../PptFileFormat/TabStop.h"
#include "../PptFileFormat/GrColorAtom.h"
#include "../PptFileFormat/ParagraphRun.h"
#include "../PptFileFormat/CharacterRun.h"
#include "../PptFileFormat/SlidePersistAtom.h"
#include "../PptFileFormat/TextHeaderAtom.h"
#include "../PptFileFormat/OutlineTextRefAtom.h"
#include "../PptFileFormat/SlideListWithText.h"
#include "../PptFileFormat/DocumentContainer.h"
#include "../PptFileFormat/Slide.h"
#include "../PptFileFormat/MainMaster.h"
#include "../PptFileFormat/Note.h"
#include "../PptFileFormat/Handout.h"
#include "../PptFileFormat/PowerPointDocument.h"

#include "../PptFileFormat/PPDrawing.h"
#include "../PptFileFormat/DrawingContainer.h"
#include "../PptFileFormat/GroupContainer.h"
#include "../PptFileFormat/ShapeContainer.h"