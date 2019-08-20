#include "stdafx.h"
#include "InternalBitConverter.h"


InternalBitConverter::InternalBitConverter()
{
}


InternalBitConverter::InternalBitConverter(bool isLittleEndian)
{
	_IsLittleEndian = isLittleEndian;
}

InternalBitConverter::~InternalBitConverter()
{
}
