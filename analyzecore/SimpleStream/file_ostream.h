#pragma once

BEGIN_SIMPLE_STREAM_SPCE

class SimpleStream_API file_ostream
{
public:
	file_ostream();
	file_ostream(const char * file);
	file_ostream(const wchar_t * file);
	~file_ostream();

	void open(const char * file);

	void open(const wchar_t * file);

	void flush();

	void close();

	bool is_open();

	template<typename T>
	void write(const T& t);

	void write(const std::vector<char>& vec);

	void write(const char* p, size_t size);

	size_t write(const unsigned char* p, size_t size);

private:
	std::FILE* output_file_ptr;
	std::true_type m_same_type;
};

template<typename T>
void file_ostream::write(const T& t)
{
	if (output_file_ptr == nullptr)
		return;

	T t2 = t;
	simple::swap_endian_if_same_endian_is_false(t2, m_same_type);
	std::fwrite(reinterpret_cast<const void*>(&t2), sizeof(T), 1, output_file_ptr);
}



END_SIMPLE_STREAM_SPCE