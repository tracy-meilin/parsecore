#pragma once

class MainMaster 
	: public Slide
{
public:
	MainMaster();
	MainMaster(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~MainMaster();

public:
	map<wstring, wstring> m_mapLayouts;
};

