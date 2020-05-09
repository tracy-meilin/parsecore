#include "stdafx.h"
#include "stdio.h"
#include "DebugPrintf.h"


void debugprintf(wchar_t* format, ...)
{
	wchar_t buff[1024] = {};
	va_list list;
	va_start(list, format);
	wvsprintf(buff + wcslen(buff), format, list);
	OutputDebugString(buff);
	va_end(list);
}