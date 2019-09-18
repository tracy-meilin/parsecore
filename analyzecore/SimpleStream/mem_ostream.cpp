#include "stdafx.h"
#include "mem_ostream.h"

BEGIN_SIMPLE_STREAM_SPCE

mem_ostream::mem_ostream()
{
}


mem_ostream::~mem_ostream()
{
}

void mem_ostream::close()
{
	m_vec.clear();
}
const std::vector<char>& mem_ostream::get_internal_vec()
{
	return m_vec;
}

void mem_ostream::write(const std::vector<char>& vec)
{
	m_vec.insert(m_vec.end(), vec.begin(), vec.end());
}
void mem_ostream::write(const char* p, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		m_vec.push_back(p[i]);
}

END_SIMPLE_STREAM_SPCE