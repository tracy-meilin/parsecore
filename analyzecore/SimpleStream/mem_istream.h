#pragma once

BEGIN_SIMPLE_STREAM_SPCE

class SimpleStream_API mem_istream
{
public:
	mem_istream();
	mem_istream(const unsigned char * mem, size_t size);
	mem_istream(const std::vector<char>& vec);

	void open(const unsigned char * mem, size_t size);

	void close();

	bool eof() const;

	std::ifstream::pos_type tellg() const;

	bool seekg(size_t pos);

	size_t seekg(std::streamoff offset, std::ios_base::seekdir way);

	const std::vector<unsigned char>& get_internal_vec();

	template<typename T>
	size_t read(T& t);

	size_t read(std::vector<char>& vec);

	size_t read(char* p, size_t size);

	size_t read(char* p, int offset, size_t size);

	size_t read(unsigned char* p, size_t size);

	size_t read(unsigned char* p, int offset, size_t size);

	size_t read(std::string& str, const unsigned int size);

	size_t getIndex(){ return m_index; }

	void setIndex(size_t index){ m_index = index; }

	size_t getLength(){ return m_vec.size(); }

	~mem_istream();

private:
	std::vector<unsigned char> m_vec;
	size_t m_index = 0;
	std::true_type m_same_type;
};

template<typename T>
size_t mem_istream::read(T& t)
{
	if (eof())
	{
		//throw std::runtime_error("Premature end of array!");
		return 0;
	}

	if ((m_index + sizeof(T)) > m_vec.size())
	{
		return 0;
		//throw std::runtime_error("Premature end of array!");
	}

	std::memcpy(reinterpret_cast<void*>(&t), &m_vec[m_index], sizeof(T));

	simple::swap_endian_if_same_endian_is_false(t, m_same_type);

	m_index += sizeof(T);

	return sizeof(T);
}

END_SIMPLE_STREAM_SPCE