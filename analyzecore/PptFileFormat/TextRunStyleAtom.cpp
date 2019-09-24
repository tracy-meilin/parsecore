#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "ParagraphRunTabStop.h"
#include "Record.h"
#include "GrColorAtom.h"
#include "CharacterRun.h"
#include "ParagraphRun.h"
#include "TextAtom.h"
#include "TextHeaderAtom.h"
#include "TextStyleAtom.h"
#include "TextRunStyleAtom.h"


TextRunStyleAtom::TextRunStyleAtom()
{
}


TextRunStyleAtom::TextRunStyleAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: TextStyleAtom(spBinaryReader, size, typeCode, version, instance)
{

}

TextRunStyleAtom::~TextRunStyleAtom()
{
}

void TextRunStyleAtom::AfterTextHeaderSet()
{
	shared_ptr<TextHeaderAtom> spTextHeaderAtom = this->GetTextHeaderAtom();
	if (spTextHeaderAtom == nullptr)
		return;

	shared_ptr<TextAtom> spTextAtom = spTextHeaderAtom->_spTextAtom;

	/* This can legitimately happen... */
	if (spTextAtom == nullptr)
	{
		_spBinaryReader->SetPosition(_spBinaryReader->GetLength());
		return;
	}

	unsigned long seenLength = 0;
	while (seenLength < spTextAtom->Text.size()+1)
	{
		long pos = _spBinaryReader->GetPosition();
		unsigned long length = _spBinaryReader->ReadUInt32();

		shared_ptr<ParagraphRun> spRun = make_shared<ParagraphRun>(_spBinaryReader, false);
		spRun->Length = length;
		m_vecPRuns.push_back(spRun);

		seenLength += length;
	}

	seenLength = 0;
	while (seenLength < spTextAtom->Text.size()+1)
	{
		unsigned long length = _spBinaryReader->ReadUInt32();

		shared_ptr<CharacterRun> spRun = make_shared<CharacterRun>(_spBinaryReader);
		spRun->Length = length;
		m_vecCRuns.push_back(spRun);

		seenLength += length;
	}

	this->VerifyReadToEnd();
}
