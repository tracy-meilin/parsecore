#include "stdafx.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "ShapeOptions.h"


ShapeOptions::ShapeOptions()
	: Record()
{
}


ShapeOptions::ShapeOptions(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	__int64 pos = _spBinaryReader->GetPosition();

	//parse the flags and the simple values
	for (int i = 0; i < instance; i++)
	{
		shared_ptr<OptionEntry> spEntry = make_shared<OptionEntry>();
		unsigned short flag = _spBinaryReader->ReadUInt16();
		spEntry->pid = ShapeOptionsSpace::PropertyId(flag & 0x3fff);
		if (flag & 0x4000)
			spEntry->fBid = true;

		if (flag & 0x8000)
			spEntry->fComplex = true;

		spEntry->op = _spBinaryReader->ReadUInt32();
		m_vecOptions.push_back(spEntry);
	}

	for (int i = 0; i < instance; ++i)
	{
		shared_ptr<OptionEntry> spEntry = m_vecOptions[i];
		if (spEntry == nullptr)
			continue;

		if (spEntry->fComplex)
		{
			if (spEntry->pid == ShapeOptionsSpace::pVertices)
			{
				int nSize = spEntry->op + 6;
				spEntry->opComplex = new unsigned char[nSize];
				memset(spEntry->opComplex, 0, nSize);
				_spBinaryReader->Read(spEntry->opComplex, nSize);
			}
			else
			{
				spEntry->opComplex = new unsigned char[spEntry->op];
				memset(spEntry->opComplex, 0, spEntry->op);
				_spBinaryReader->Read(spEntry->opComplex, spEntry->op);
			}
		}

		auto& ele = m_mapOptionsByID.find(spEntry->pid);
		if (ele != m_mapOptionsByID.end())
		{
			ele->second = spEntry;
		}
		else
		{
			m_mapOptionsByID.insert(make_pair(spEntry->pid, spEntry));
		}
	}

	_spBinaryReader->Seek(pos + size, SEEK_SET);
}

ShapeOptions::~ShapeOptions()
{
}
