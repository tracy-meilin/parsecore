#pragma once


class StructuredStorageReader
{
public:
	StructuredStorageReader();
	StructuredStorageReader(const wstring& fileName);
	~StructuredStorageReader();

private:
	shared_ptr<InputHandler> _spFileHandler = nullptr;
	shared_ptr<Header> _spHeader = nullptr;
};

