#include "stdafx.h"
#include "file_ostream.h"

BEGIN_SIMPLE_STREAM_SPCE

file_ostream::file_ostream() : output_file_ptr(nullptr)
{
}

file_ostream::file_ostream(const char * file) : output_file_ptr(nullptr)
{
	open(file);
}

file_ostream::file_ostream(const wchar_t * file) : output_file_ptr(nullptr)
{
	open(file);
}

file_ostream::~file_ostream()
{
	close();
}

void file_ostream::open(const char * file)
{
	close();
#ifdef _MSC_VER
	output_file_ptr = nullptr;
	fopen_s(&output_file_ptr, file, "wb");
#else
	output_file_ptr = std::fopen(file, "wb");
#endif
}

void file_ostream::open(const wchar_t * file)
{
	close();
	output_file_ptr = nullptr;
	_wfopen_s(&output_file_ptr, file, L"wb");
}

void file_ostream::flush()
{
	std::fflush(output_file_ptr);
}

void file_ostream::close()
{
	if (output_file_ptr)
	{
		std::fclose(output_file_ptr);
		output_file_ptr = nullptr;
	}
}

bool file_ostream::is_open()
{
	return output_file_ptr != nullptr;
}

void file_ostream::write(const std::vector<char>& vec)
{
	if (output_file_ptr == nullptr)
		return;

	std::fwrite(reinterpret_cast<const void*>(&vec[0]), vec.size(), 1, output_file_ptr);
}
void file_ostream::write(const char* p, size_t size)
{
	if (output_file_ptr == nullptr)
		return;

	std::fwrite(reinterpret_cast<const void*>(p), size, 1, output_file_ptr);
}
size_t file_ostream::write(const unsigned char* p, size_t size)
{
	if (output_file_ptr == nullptr)
		return 0;

	return std::fwrite(reinterpret_cast<const void*>(p), size, 1, output_file_ptr);
}

END_SIMPLE_STREAM_SPCE