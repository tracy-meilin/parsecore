#include "stdafx.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "MasterTextPropAtom.h"


MasterTextPropAtom::MasterTextPropAtom()
{
}


MasterTextPropAtom::MasterTextPropAtom(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: Record(spBinaryReader, size, typeCode, version, instance)
{
	while (_spBinaryReader->GetPosition() < _spBinaryReader->GetLength())
	{
		MasterTextPropRun run;
		run.count = _spBinaryReader->ReadUInt32();
		run.indentLevel = _spBinaryReader->ReadUInt16();
		m_vecMasterTextPropRuns.push_back(run);
	}
}

MasterTextPropAtom::~MasterTextPropAtom()
{
}
