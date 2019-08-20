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

unsigned long InputHandler::GetIOStreamSize()
{
	return _spStream->file_length();
}

void InputHandler::ReadPosition(char* p, size_t size, long position)
{
	if (position < 0)
		return;

	_spStream->seekg(position, 0);
	_spStream->read(p, size);
}
