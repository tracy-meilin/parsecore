#include "stdafx.h"
#include "SimpleBinStream.h"
#include "BaseStream.h"
#include "FileStream.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"
#include "Record.h"
#include "XmlRecord.h"
#include "XmlContainer.h"


XmlContainer::XmlContainer()
{
}


XmlContainer::XmlContainer(shared_ptr<BinaryReader> spBinaryReader, 
	unsigned long size, 
	unsigned long typeCode, 
	unsigned int version, 
	unsigned int instance)
	: XmlRecord(spBinaryReader, size, typeCode, version, instance)
{
	TCHAR lpTempPathBuffer[MAX_PATH];
	TCHAR szTempFileName[MAX_PATH];

	DWORD dwRt = GetTempPath(MAX_PATH,          // length of the buffer
						lpTempPathBuffer); // buffer for path 

	dwRt = GetTempFileName(lpTempPathBuffer, // directory for tmp files
		_T("ND_TMP"),     // temp file name prefix 
		0,                // create unique name 
		szTempFileName);  // buffer for name 

	shared_ptr<FileStream> spFileStream = make_shared<FileStream>(szTempFileName);
	if (spFileStream)
	{
		shared_ptr<BinaryWriter> spBinaryWriter = make_shared<BinaryWriter>(spFileStream);
		if (spBinaryWriter)
		{
			__int64 nSize = _spBinaryReader->GetLength();
			unsigned char* bytes = new unsigned char[nSize];
			_spBinaryReader->Read(bytes, nSize);

			spBinaryWriter->Write(bytes, nSize);
			spBinaryWriter->Close();
			spFileStream->Close();
		}
	}
}

XmlContainer::~XmlContainer()
{
}
