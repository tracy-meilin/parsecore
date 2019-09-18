#pragma once

BEGIN_SIMPLE_STREAM_SPCE

class SimpleStream_API ptr_istream
{
public:
	ptr_istream();
	ptr_istream(const char * mem, size_t size);
	ptr_istream(const std::vector<char>& vec);
	~ptr_istream();

	void open(const char * mem, size_t size);

	void close();

	bool eof() const;

	std::ifstream::pos_type tellg() const;

	bool seekg(size_t pos);

	bool seekg(std::streamoff offset, std::ios_base::seekdir way);

	template<typename T>
	void read(T& t);

	void read(std::vector<char>& vec);

	void read(char* p, size_t size);

	void read(std::string& str, const unsigned int size);

private:
	const char* m_arr;
	size_t m_size;
	size_t m_index;
	std::true_type m_same_type;
};

template<typename T>
void ptr_istream::read(T& t)
{
	if (eof())
		return;
		//throw std::runtime_error("Premature end of array!");

	if ((m_index + sizeof(T)) > m_size)
		return;
		//throw std::runtime_error("Premature end of array!");

	std::memcpy(reinterpret_cast<void*>(&t), &m_arr[m_index], sizeof(T));

	simple::swap_endian_if_same_endian_is_false(t, m_same_type);

	m_index += sizeof(T);
}

template<typename T>
ptr_istream& operator >> (ptr_istream& istm, T& val)
{
	istm.read(val);

	return istm;
}

ptr_istream& operator >> (ptr_istream& istm, std::string& val)
{
	val.clear();

	int size = 0;
	istm.read(size);

	if (size <= 0)
		return istm;

	istm.read(val, size);

	return istm;
}

END_SIMPLE_STREAM_SPCE