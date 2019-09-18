#include "stdafx.h"
#include "memfile_ostream.h"

BEGIN_SIMPLE_STREAM_SPCE

memfile_ostream::memfile_ostream()
{
}


memfile_ostream::~memfile_ostream()
{
}

void memfile_ostream::close()
{
	m_vec.clear();
}
const std::vector<char>& memfile_ostream::get_internal_vec()
{
	return m_vec;
}

void memfile_ostream::write(const std::vector<char>& vec)
{
	m_vec.insert(m_vec.end(), vec.begin(), vec.end());
}
void memfile_ostream::write(const char* p, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		m_vec.push_back(p[i]);
}
bool memfile_ostream::write_to_file(const char* file)
{
#ifdef _MSC_VER
	std::FILE* fp = nullptr;
	fopen_s(&fp, file, "wb");
#else
	std::FILE* fp = std::fopen(file, "wb");
#endif
	if (fp)
	{
		size_t size = std::fwrite(m_vec.data(), m_vec.size(), 1, fp);
		std::fflush(fp);
		std::fclose(fp);
		m_vec.clear();
		return size == 1u;
	}
	return false;
}

bool memfile_ostream::write_to_file(const wchar_t* file)
{
	std::FILE* fp = nullptr;
	_wfopen_s(&fp, file, L"wb");
	if (fp)
	{
		size_t size = std::fwrite(m_vec.data(), m_vec.size(), 1, fp);
		std::fflush(fp);
		std::fclose(fp);
		m_vec.clear();
		return size == 1u;
	}
	return false;
}

END_SIMPLE_STREAM_SPCE