#pragma once

class InputHandler 
	: public AbstractIOHandler
{
public:
	InputHandler();
	InputHandler(const wstring& fileName);
	InputHandler(shared_ptr<simple::file_istream<std::true_type>>& spStream);
	~InputHandler();

	virtual unsigned long GetIOStreamSize() override;

	/// <summary>
	/// Reads bytes at the given position of the file stream into a byte array.
	/// The array size determines the number of bytes to read.
	/// Advances the stream pointer accordingly.
	/// </summary>
	void ReadPosition(char* p, size_t size, long position);

private:
	//simple::memfile_istream<std::true_type> _stream("file4.bin");
};

