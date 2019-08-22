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
	shared_ptr<Fat> _spFat = nullptr;
	shared_ptr<DirectoryTree> _spDirectory = nullptr;
	shared_ptr<MiniFat> _spMiniFat = nullptr;
};

