#include "stdafx.h"
#include "GlobalDefines.h"
#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

bool Utils::BitmaskToBool(signed long value, signed long mask)
{
	return ((value & mask) == mask);
}

bool Utils::BitmaskToBool(unsigned long value, unsigned long mask)
{
	return ((value & mask) == mask);
}

bool Utils::BitmaskToBool(signed short value, signed short mask)
{
	return ((value & mask) == mask);
}

bool Utils::BitmaskToBool(unsigned short value, unsigned short mask)
{
	return ((value & mask) == mask);
}

std::wstring Utils::PlaceholderIdToXMLValue(OEPlaceHolderAtomSpace::PlaceholderEnum pid)
{
	wstring strResult = _T("");
	return strResult;
}
