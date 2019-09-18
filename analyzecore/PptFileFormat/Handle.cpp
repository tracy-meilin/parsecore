#include "stdafx.h"
#include "Handle.h"


Handle::Handle()
{
}


Handle::Handle(wstring pos, wstring xRange)
{
	this->position = pos;
	this->xrange = xrange;
}

Handle::~Handle()
{
}
