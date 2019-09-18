#include "stdafx.h"
#include "ptr_istream.h"

BEGIN_SIMPLE_STREAM_SPCE

ptr_istream::ptr_istream() : m_arr(nullptr), m_size(0), m_index(0)
{
}

ptr_istream::ptr_istream(const char * mem, size_t size) : m_arr(nullptr), m_size(0), m_index(0)
{
	open(mem, size);
}

ptr_istream::ptr_istream(const std::vector<char>& vec)
{
	m_index = 0;
	m_arr = vec.data();
	m_size = vec.size();
}

ptr_istream::~ptr_istream()
{
}

void ptr_istream::open(const char * mem, size_t size)
{
	m_index = 0;
	m_arr = mem;
	m_size = size;
}

void ptr_istream::close()
{
	m_arr = nullptr; m_size = 0; m_index = 0;
}

bool ptr_istream::eof() const
{
	return m_index >= m_size;
}

std::ifstream::pos_type ptr_istream::tellg() const
{
	return m_index;
}

bool ptr_istream::seekg(size_t pos)
{
	if (pos < m_size)
		m_index = pos;
	else
		return false;

	return true;
}

bool ptr_istream::seekg(std::streamoff offset, std::ios_base::seekdir way)
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

void ptr_istream::read(std::vector<char>& vec)
{
	if (eof())
		throw std::runtime_error("Premature end of array!");

	if ((m_index + vec.size()) > m_size)
		throw std::runtime_error("Premature end of array!");

	std::memcpy(reinterpret_cast<void*>(&vec[0]), &m_arr[m_index], vec.size());

	m_index += vec.size();
}

void ptr_istream::read(char* p, size_t size)
{
	if (eof())
		throw std::runtime_error("Premature end of array!");

	if ((m_index + size) > m_size)
		throw std::runtime_error("Premature end of array!");

	std::memcpy(reinterpret_cast<void*>(p), &m_arr[m_index], size);

	m_index += size;
}

void ptr_istream::read(std::string& str, const unsigned int size)
{
	if (eof())
		throw std::runtime_error("Premature end of array!");

	if ((m_index + size) > m_size)
		throw std::runtime_error("Premature end of array!");

	str.assign(&m_arr[m_index], size);

	m_index += str.size();
}

END_SIMPLE_STREAM_SPCE