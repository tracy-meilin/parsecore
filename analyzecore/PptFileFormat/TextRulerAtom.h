#pragma once

class TextRulerAtom 
	: public Record
{
public:
	TextRulerAtom();
	TextRulerAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~TextRulerAtom();

public:
	unsigned long flags;
	bool fDefaultTabSize;
	bool fCLevels;
	bool fTabStops;
	bool fLeftMargin1;
	bool fLeftMargin2;
	bool fLeftMargin3;
	bool fLeftMargin4;
	bool fLeftMargin5;
	bool fIndent1;
	bool fIndent2;
	bool fIndent3;
	bool fIndent4;
	bool fIndent5;

	signed long cLevels;
	signed long defaultTabSize;
	shared_ptr<TabStops> m_spTabs = nullptr;
	signed long leftMargin1;
	signed long leftMargin2;
	signed long leftMargin3;
	signed long leftMargin4;
	signed long leftMargin5;
	signed long indent1;
	signed long indent2;
	signed long indent3;
	signed long indent4;
	signed long indent5;
};

class TextRulerTabStop
{
public:
	TextRulerTabStop(shared_ptr<BinaryReader> spBinaryReader);
	~TextRulerTabStop();

public:
	unsigned long position;
	TextRulerAtomSpace::TextTabTypeEnum TabType;
};

class TabStops
{
public:
	TabStops(shared_ptr<BinaryReader> spBinaryReader);
	~TabStops();

public:
	unsigned long count;
	vector<shared_ptr<TextRulerTabStop>> m_vecTabStops;
};
