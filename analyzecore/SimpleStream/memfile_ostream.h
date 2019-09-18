#pragma once

BEGIN_SIMPLE_STREAM_SPCE

class SimpleStream_API memfile_ostream
{
public:
	memfile_ostream();
	~memfile_ostream();

	void close();

	const std::vector<char>& get_internal_vec();

	template<typename T>
	void write(const T& t);

	void write(const std::vector<char>& vec);

	void write(const char* p, size_t size);

	bool write_to_file(const char* file);

	bool write_to_file(const wchar_t* file);

private:
	std::vector<char> m_vec;
	std::true_type m_same_type;
};

template<typename T>
void memfile_ostream::write(const T& t)
{
	std::vector<char> vec(sizeof(T));
	T t2 = t;
	simple::swap_endian_if_same_endian_is_false(t2, m_same_type);
	std::memcpy(reinterpret_cast<void*>(&vec[0]), reinterpret_cast<const void*>(&t2), sizeof(T));
	write(vec);
}

template<typename T>
memfile_ostream& operator << (memfile_ostream& ostm, const T& val)
{
	ostm.write(val);

	return ostm;
}

memfile_ostream& operator << (memfile_ostream& ostm, const std::string& val)
{
	int size = val.size();
	ostm.write(size);

	if (val.size() <= 0)
		return ostm;

	ostm.write(val.c_str(), val.size());

	return ostm;
}

memfile_ostream& operator << (memfile_ostream& ostm, const char* val)
{
	int size = std::strlen(val);
	ostm.write(size);

	if (size <= 0)
		return ostm;

	ostm.write(val, size);

	return ostm;
}

END_SIMPLE_STREAM_SPCE