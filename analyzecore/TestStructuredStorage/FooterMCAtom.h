#pragma once

class FooterMCAtom
	: public Record
{
public:
	FooterMCAtom();
	FooterMCAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
 	virtual ~FooterMCAtom();

public:
	signed long Position;
};

//////////////////////////////////////////////////////////////////////////

class DateTimeMCAtom
	: public Record
{
public:
	DateTimeMCAtom();
	DateTimeMCAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~DateTimeMCAtom();

public:
	signed long Position;
	unsigned char index;
};

//////////////////////////////////////////////////////////////////////////

class HeaderMCAtom
	: public Record
{
public:
	HeaderMCAtom();
	HeaderMCAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~HeaderMCAtom();

public:
	signed long Position;
};

//////////////////////////////////////////////////////////////////////////

class SlideNumberMCAtom
	: public Record
{
public:
	SlideNumberMCAtom();
	SlideNumberMCAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~SlideNumberMCAtom();

public:
	signed long Position;
};

//////////////////////////////////////////////////////////////////////////
class GenericDateMCAtom
	: public Record
{
public:
	GenericDateMCAtom();
	GenericDateMCAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~GenericDateMCAtom();

public:
	signed long Position;
};