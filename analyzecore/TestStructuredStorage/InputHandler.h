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

	/// <summary>
	/// Reads bytes at the given position of the file stream into a byte array.
	/// The array size determines the number of bytes to read.
	/// Advances the stream pointer accordingly.
	/// </summary>
	void ReadPosition(unsigned char* p, size_t size, long position);

	void ReadChar(char& r);

	void ReadChar(unsigned char& r);

	void Read(unsigned char* p, size_t size);

	void Read(unsigned char* p, int offset, size_t size);

	void Read(char* p, size_t size);

	unsigned __int64 ReadUInt64(long position);

	unsigned __int64 ReadUInt64();

	unsigned short ReadUInt16(long position);

	unsigned short ReadUInt16();

	unsigned long ReadUInt32(long position);

	unsigned long ReadUInt32();

	wstring ReadUnicodeString(int size);

	long SeekToSector(long sector);

	/// <summary>
	/// Seeks to a given sector and position in the compound file.
	/// May only be used after SetHeaderReference() is called.
	/// </summary>
	/// <returns>The new position in the stream.</returns>
	long SeekToPositionInSector(__int64 sector, __int64 position);

private:
	//simple::memfile_istream<std::true_type> _stream("file4.bin");
};

