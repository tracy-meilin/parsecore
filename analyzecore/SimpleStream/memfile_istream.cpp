#include "stdafx.h"
#include "memfile_istream.h"

BEGIN_SIMPLE_STREAM_SPCE

memfile_istream::memfile_istream() : m_arr(nullptr), m_size(0), m_index(0)
{
}

memfile_istream::memfile_istream(const char * file) : m_arr(nullptr), m_size(0), m_index(0)
{
	open(file);
}

memfile_istream::memfile_istream(const wchar_t * file) : m_arr(nullptr), m_size(0), m_index(0)
{
	open(file);
}

memfile_istream::~memfile_istream()
{
	close();
}

void memfile_istream::open(const char * file)
{
	close();
#ifdef _MSC_VER
	std::FILE* input_file_ptr = nullptr;
	fopen_s(&input_file_ptr, file, "rb");
#else
	std::FILE* input_file_ptr = std::fopen(file, "rb");
#endif
	compute_length(input_file_ptr);
	m_arr = new char[m_size];
	std::fread(m_arr, m_size, 1, input_file_ptr);
	fclose(input_file_ptr);
}

void memfile_istream::open(const wchar_t * file)
{
	close();
	std::FILE* input_file_ptr = nullptr;
	_wfopen_s(&input_file_ptr, file, L"rb");
	compute_length(input_file_ptr);
	m_arr = new char[m_size];
	std::fread(m_arr, m_size, 1, input_file_ptr);
	fclose(input_file_ptr);
}

void memfile_istream::close()
{
	if (m_arr)
	{
		delete[] m_arr;
		m_arr = nullptr; m_size = 0; m_index = 0;
	}
}

bool memfile_istream::is_open()
{
	return (m_arr != nullptr);
}

long memfile_istream::file_length() const
{
	return m_size;
}

bool memfile_istream::eof() const
{
	return m_index >= m_size;
}

std::ifstream::pos_type memfile_istream::tellg() const
{
	return m_index;
}

bool memfile_istream::seekg(size_t pos)
{
	if (pos < m_size)
		m_index = pos;
	else
		return false;

	return true;
}

bool memfile_istream::seekg(std::streamoff offset, std::ios_base::seekdir way)
{
	if (way == std::ios_base::beg && offset < m_size)
		m_index = offset;
	else if (way == std::ios_base::cur && (m_index + offset) < m_size)
		m_index += offset;
	else if (way == std::ios_base::end && (m_size + offset) < m_size)
		m_index = m_size + offset;
	else
		return false;

	return true;
}

void memfile_istream::read(std::vector<char>& vec)
{
	if (eof())
		throw std::runtime_error("Premature end of array!");

	if ((m_index + vec.size()) > m_size)
		throw std::runtime_error("Premature end of array!");

	std::memcpy(reinterpret_cast<void*>(&vec[0]), &m_arr[m_index], vec.size());

	m_index += vec.size();
}

void memfile_istream::read(char* p, size_t size)
{
	if (eof())
		throw std::runtime_error("Premature end of array!");

	if ((m_index + size) > m_size)
		throw std::runtime_error("Premature end of array!");

	std::memcpy(reinterpret_cast<void*>(p), &m_arr[m_index], size);

	m_index += size;
}

void memfile_istream::read(std::string& str, const unsigned int size)
{
	if (eof())
		throw std::runtime_error("Premature end of array!");

	if ((m_index + size) > m_size)
		throw std::runtime_error("Premature end of array!");

	str.assign(&m_arr[m_index], size);

	m_index += str.size();
}

void memfile_istream::compute_length(std::FILE* input_file_ptr)
{
	std::fseek(input_file_ptr, 0, SEEK_END);
	m_size = std::ftell(input_file_ptr);
	std::fseek(input_file_ptr, 0, SEEK_SET);
}

END_SIMPLE_STREAM_SPCE