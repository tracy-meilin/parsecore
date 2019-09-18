#pragma once

BEGIN_SIMPLE_STREAM_SPCE

class SimpleStream_API file_istream
{
public:
	file_istream();
	file_istream(const char * file);
	file_istream(const wchar_t * file);
	~file_istream();

	void open(const char * file);

	void open(const wchar_t * file);

	void close();

	bool is_open();

	long file_length() const;

	// http://www.cplusplus.com/reference/cstdio/feof/
	// stream's internal position indicator may point to the end-of-file for the 
	// next operation, but still, the end-of-file indicator may not be set until 
	// an operation attempts to read at that point.
	bool eof() const; // not using feof(), see above
	long tellg() const;
	void seekg(long pos);
	void seekg(long offset, int way);

	template<typename T>
	size_t read(T& t);

	size_t read(std::vector<char>& vec);

	size_t read(char* p, size_t size);

	size_t read(unsigned char* p, size_t size);

	size_t read(unsigned char* p, int offset, size_t size);

private:
	void compute_length();

private:
	std::FILE* input_file_ptr;
	long file_size;
	long read_length;
	std::true_type m_same_type;
};

template<typename T>
size_t file_istream::read(T& t)
{
	if (input_file_ptr == nullptr)
		return 0;

	if (std::fread(reinterpret_cast<void*>(&t), sizeof(T), 1, input_file_ptr) != 1)
	{
		//throw std::runtime_error("Read Error!");
		return 0;
	}
	read_length += sizeof(T);
	simple::swap_endian_if_same_endian_is_false(t, m_same_type);

	return sizeof(T);
}


END_SIMPLE_STREAM_SPCE
