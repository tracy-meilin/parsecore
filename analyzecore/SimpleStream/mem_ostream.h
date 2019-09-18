#pragma once

BEGIN_SIMPLE_STREAM_SPCE

class SimpleStream_API mem_ostream
{
public:
	mem_ostream();
	~mem_ostream();

	void close();

	const std::vector<char>& get_internal_vec();

	template<typename T>
	void write(const T& t);

	void write(const std::vector<char>& vec);

	void write(const char* p, size_t size);

private:
	std::vector<char> m_vec;
	std::true_type m_same_type;
};

template<typename T>
void mem_ostream::write(const T& t)
{
	std::vector<char> vec(sizeof(T));
	T t2 = t;
	simple::swap_endian_if_same_endian_is_false(t2, m_same_type);
	std::memcpy(reinterpret_cast<void*>(&vec[0]), reinterpret_cast<const void*>(&t2), sizeof(T));
	write(vec);
}


template<typename T>
mem_ostream& operator << (mem_ostream& ostm, const T& val)
{
	ostm.write(val);

	return ostm;
}


mem_ostream& operator << (mem_ostream& ostm, const std::string& val)
{
	int size = val.size();
	ostm.write(size);

	if (val.size() <= 0)
		return ostm;

	ostm.write(val.c_str(), val.size());

	return ostm;
}


mem_ostream& operator << (mem_ostream& ostm, const char* val)
{
	int size = std::strlen(val);
	ostm.write(size);

	if (size <= 0)
		return ostm;

	ostm.write(val, size);

	return ostm;
}

END_SIMPLE_STREAM_SPCE