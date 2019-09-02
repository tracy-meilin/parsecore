#pragma once

struct OptionEntry
{
	ShapeOptionsSpace::PropertyId pid;
	bool fBid = false;
	bool fComplex = false;
	unsigned long op;
	unsigned char* opComplex = nullptr;
};

class ShapeOptions 
	: public Record
{
public:
	ShapeOptions();
	ShapeOptions(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);

	~ShapeOptions();

public:
	map<ShapeOptionsSpace::PropertyId, shared_ptr<OptionEntry>> m_mapOptionsByID;
	vector<shared_ptr<OptionEntry>> m_vecOptions;
};

