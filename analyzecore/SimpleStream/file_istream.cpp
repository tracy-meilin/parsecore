#include "stdafx.h"
#include "file_istream.h"

BEGIN_SIMPLE_STREAM_SPCE

file_istream::file_istream() 
	: input_file_ptr(nullptr), file_size(0L), read_length(0L)
{
}

file_istream::file_istream(const char * file) 
	: input_file_ptr(nullptr), file_size(0L), read_length(0L)
{
	open(file);
}

file_istream::file_istream(const wchar_t * file) 
	: input_file_ptr(nullptr), file_size(0L), read_length(0L)
{
	open(file);
}

file_istream::~file_istream()
{
	close();
}

void file_istream::open(const char * file)
{
	close();
#ifdef _MSC_VER
	input_file_ptr = nullptr;
	fopen_s(&input_file_ptr, file, "rb");
#else
	input_file_ptr = std::fopen(file, "rb");
#endif
	compute_length();
}

void file_istream::open(const wchar_t * file)
{
	close();
	input_file_ptr = nullptr;
	_wfopen_s(&input_file_ptr, file, L"rb");
	compute_length();
}

void file_istream::close()
{
	if (input_file_ptr)
	{
		fclose(input_file_ptr);
		input_file_ptr = nullptr;
	}
}

bool file_istream::is_open()
{
	return (input_file_ptr != nullptr);
}

long file_istream::file_length() const
{
	return file_size;
}

bool file_istream::eof() const
{
	return read_length >= file_size;
}

long file_istream::tellg() const
{
	if (input_file_ptr)
		return std::ftell(input_file_ptr);

	return 0;
}

void file_istream::seekg(long pos)
{
	if (input_file_ptr)
		std::fseek(input_file_ptr, pos, SEEK_SET);
}

void file_istream::seekg(long offset, int way)
{
	if (input_file_ptr)
		std::fseek(input_file_ptr, offset, way);
}

size_t file_istream::read(std::vector<char>& vec)
{
	if (input_file_ptr == nullptr)
		return 0;

	if (std::fread(reinterpret_cast<void*>(&vec[0]), vec.size(), 1, input_file_ptr) != 1)
	{
		//throw std::runtime_error("Read Error!");
		return 0;
	}
	read_length += vec.size();

	return vec.size();
}

size_t file_istream::read(char* p, size_t size)
{
	if (input_file_ptr == nullptr)
		return 0;

	if (std::fread(reinterpret_cast<void*>(p), size, 1, input_file_ptr) != 1)
	{
		//throw std::runtime_error("Read Error!");
		return 0;
	}
	read_length += size;

	return size;
}

size_t file_istream::read(unsigned char* p, size_t size)
{
	if (input_file_ptr == nullptr)
		return 0;

	if (std::fread(reinterpret_cast<void*>(p), size, 1, input_file_ptr) != 1)
	{
		//throw std::runtime_error("Read Error!");
		return 0;
	}
	read_length += size;

	return size;
}

size_t file_istream::read(unsigned char* p, int offset, size_t size)
{
	if (input_file_ptr == nullptr)
		return 0;

	unsigned char* tmp = p + offset;	//TODO:指针判断，是否越界访问
	if (std::fread(reinterpret_cast<void*>(tmp), size, 1, input_file_ptr) != 1)
	{
		//throw std::runtime_error("Read Error!");
		return 0;
	}
	read_length += size;

	return size;
}

void file_istream::compute_length()
{
	seekg(0, SEEK_END);
	file_size = tellg();
	seekg(0, SEEK_SET);
}

END_SIMPLE_STREAM_SPCE