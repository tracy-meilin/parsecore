#pragma once

class InputHandler 
	: public AbstractIOHandler
{
public:
	InputHandler();
	InputHandler(const wstring& fileName);
	InputHandler(shared_ptr<simple::file_istream<std::true_type>>& spStream);
	~InputHandler();

private:
	//simple::memfile_istream<std::true_type> _stream("file4.bin");
};

