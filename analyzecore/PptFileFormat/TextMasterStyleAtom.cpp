#include "stdafx.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "ParagraphRunTabStop.h"
#include "GrColorAtom.h"
#include "ParagraphRun.h"
#include "CharacterRun.h"
#include "Record.h"

#include "TextStyleAtom.h"
#include "TextMasterStyleAtom.h"


TextMasterStyleAtom::TextMasterStyleAtom()
{
}

TextMasterStyleAtom::TextMasterStyleAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: TextStyleAtom(spBinaryReader, size, typeCode, version, instance)
{
	this->Bytes = new unsigned char[this->BodySize];
	_spBinaryReader->Read(this->Bytes, this->BodySize);
	_spBinaryReader->SetPosition(0);

	this->IndentLevelCount = _spBinaryReader->ReadUInt16();
	for (int i = 0; i < this->IndentLevelCount; i++)
	{
		long pos = _spBinaryReader->GetPosition();

		if (this->Instance >= 5)
		{
			unsigned short level = _spBinaryReader->ReadUInt16();
		}

		this->m_vecPRuns.push_back(make_shared<ParagraphRun>(this->_spBinaryReader, true));

		pos = this->_spBinaryReader->GetPosition();
		this->m_vecCRuns.push_back(make_shared<CharacterRun>(this->_spBinaryReader));
	}

	if (this->_spBinaryReader->GetPosition() != this->_spBinaryReader->GetLength())
	{
		this->_spBinaryReader->SetPosition(this->_spBinaryReader->GetLength());
	}
}

TextMasterStyleAtom::~TextMasterStyleAtom()
{
	if (this->Bytes != nullptr)
	{
		delete[] this->Bytes;
	}
}
