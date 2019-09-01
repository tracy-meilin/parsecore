#include "stdafx.h"
#include "GlobalDefines.h"

#include "BaseStream.h"
#include "BinaryReader.h"
#include "TabStop.h"
#include "Record.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"


ParagraphRun::ParagraphRun()
{
}


ParagraphRun::ParagraphRun(shared_ptr<BinaryReader> spBinaryReader, bool noIndentField)
{
	this->IndentLevel = noIndentField ? 0 : spBinaryReader->ReadUInt16();
	this->mask = (Common::ParagraphMask)spBinaryReader->ReadUInt32();

	// Note: These appear in Mask as well -- there they are true
	// when the flag differs from the Master style.
	// The actual value for the differing flags is stored here.
	// (TODO: This is still a guess. Verify.)
	if (this->GetBulletFlagsFieldPresent())
		this->BulletFlags = spBinaryReader->ReadUInt16();

	if (this->GetBulletCharPresent())
		this->BulletChar = (wchar_t)spBinaryReader->ReadUInt16();

	if (this->GetBulletFontPresent())
		this->BulletTypefaceIdx = spBinaryReader->ReadUInt16();

	if (this->GetBulletSizePresent())
		this->BulletSize = spBinaryReader->ReadInt16();

	if (this->GetBulletColorPresent())
		this->_spBulletColor = make_shared<GrColorAtom>(spBinaryReader);

	if (this->GetAlignmentPresent())
		this->Alignment = spBinaryReader->ReadInt16();

	if (this->GetLineSpacingPresent())
		this->LineSpacing = spBinaryReader->ReadInt16();

	if (this->GetSpaceBeforePresent())
		this->SpaceBefore = spBinaryReader->ReadInt16();

	if (this->GetSpaceAfterPresent())
		this->SpaceAfter = spBinaryReader->ReadInt16();

	if (this->GetLeftMarginPresent())
		this->LeftMargin = spBinaryReader->ReadInt16();

	if (this->GetIndentPresent())
		this->Indent = spBinaryReader->ReadInt16();

	if (this->GetDefaultTabSizePresent())
		this->DefaultTabSize = spBinaryReader->ReadInt16();

	if (this->GetTabStopsPresent())
	{
		unsigned short tabStopsCount = spBinaryReader->ReadUInt16();
		//this.TabStops = new TabStop[tabStopsCount];

		for (int i = 0; i < tabStopsCount; i++)
		{
			m_vecTabStop.push_back(make_shared<TabStop>(spBinaryReader));
			//this.TabStops[i] = new TabStop(reader);
		}
	}

	if (this->GetFontAlignPresent())
		this->FontAlign = spBinaryReader->ReadUInt16();

	if (this->GetLineBreakFlagsFieldPresent())
		this->LineBreakFlags = spBinaryReader->ReadUInt16();

	if (this->GetTextDirectionPresent())
		this->_TextDirectioin = spBinaryReader->ReadUInt16();
}

ParagraphRun::~ParagraphRun()
{
}
