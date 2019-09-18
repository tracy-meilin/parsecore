#include "stdafx.h"
#include "mem_istream.h"

BEGIN_SIMPLE_STREAM_SPCE

mem_istream::mem_istream() : m_index(0)
{
}

mem_istream::mem_istream(const unsigned char * mem, size_t size)
{
	open(mem, size);
}

mem_istream::mem_istream(const std::vector<char>& vec)
{
	m_index = 0;
	m_vec.reserve(vec.size());
	m_vec.assign(vec.begin(), vec.end());
}

mem_istream::~mem_istream()
{
}


void mem_istream::open(const unsigned char * mem, size_t size)
{
	m_index = 0;
	m_vec.clear();
	m_vec.reserve(size);
	m_vec.assign(mem, mem + size);
}

void mem_istream::close()
{
	m_vec.clear();
}

bool mem_istream::eof() const
{
	return m_index >= m_vec.size();
}

std::ifstream::pos_type mem_istream::tellg() const
{
	return m_index;
}

bool mem_istream::seekg(size_t pos)
{
	if (pos < m_vec.size())
		m_index = pos;
	else
		return false;

	return true;
}

size_t mem_istream::seekg(std::streamoff offset, std::ios_base::seekdir way)
{
	if (way == std::ios_base::beg && offset < m_vec.size())
		m_index = offset;
	else if (way == std::ios_base::cur && (m_index + offset) < m_vec.size())
		m_index += offset;
	else if (way == std::ios_base::end && (m_vec.size() + offset) < m_vec.size())
		m_index = m_vec.size() + offset;

	return m_index;
}

const std::vector<unsigned char>& mem_istream::get_internal_vec()
{
	return m_vec;
}

size_t mem_istream::read(std::vector<char>& vec)
{
	if (eof())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	if ((m_index + vec.size()) > m_vec.size())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	std::memcpy(reinterpret_cast<void*>(&vec[0]), &m_vec[m_index], vec.size());

	m_index += vec.size();

	return vec.size();
}

size_t mem_istream::read(char* p, size_t size)
{
	if (eof())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	if ((m_index + size) > m_vec.size())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	std::memcpy(reinterpret_cast<void*>(p), &m_vec[m_index], size);

	m_index += size;

	return size;
}

size_t mem_istream::read(char* p, int offset, size_t size)
{
	if (eof())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	if ((m_index + size) > m_vec.size())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	char* tmp = p + offset;	//TODO:指针判断，是否越界访问
	std::memcpy(reinterpret_cast<void*>(tmp), &m_vec[m_index], size);

	m_index += size;

	return size;
}

size_t mem_istream::read(unsigned char* p, size_t size)
{
	if (eof())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	if ((m_index + size) > m_vec.size())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	std::memcpy(reinterpret_cast<void*>(p), &m_vec[m_index], size);

	m_index += size;

	return size;
}

size_t mem_istream::read(unsigned char* p, int offset, size_t size)
{
	if (eof())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	if ((m_index + size) > m_vec.size())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	unsigned char* tmp = p + offset;	//TODO:指针判断，是否越界访问
	std::memcpy(reinterpret_cast<void*>(tmp), &m_vec[m_index], size);

	m_index += size;

	return size;
}

size_t mem_istream::read(std::string& str, const unsigned int size)
{
	if (eof())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	if ((m_index + size) > m_vec.size())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	str.assign((char)&m_vec[m_index], size);

	m_index += str.size();

	return size;
}



END_SIMPLE_STREAM_SPCE