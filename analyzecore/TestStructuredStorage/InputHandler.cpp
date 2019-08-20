#include "stdafx.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "AbstractHeader.h"
#include "InputHandler.h"


InputHandler::InputHandler()
{
}


InputHandler::InputHandler(const wstring& fileName)
{
	_spStream = make_shared<simple::file_istream<std::true_type>>(fileName.c_str());
}

InputHandler::InputHandler(shared_ptr<simple::file_istream<std::true_type>>& spStream)
{
	_spStream = spStream;
}

InputHandler::~InputHandler()
{
}
