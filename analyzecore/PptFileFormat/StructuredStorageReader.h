#pragma once


class PptFileFormat_API StructuredStorageReader
{
public:
	StructuredStorageReader();
	StructuredStorageReader(const wstring& fileName);
	~StructuredStorageReader();

	shared_ptr<VirtualStream> GetStream(wstring path);

	vector<wstring> GetFullNameOfAllStreamEntries();

private:
	shared_ptr<InputHandler> _spFileHandler = nullptr;
	shared_ptr<Header> _spHeader = nullptr;
	shared_ptr<Fat> _spFat = nullptr;
	shared_ptr<DirectoryTree> _spDirectory = nullptr;
	shared_ptr<MiniFat> _spMiniFat = nullptr;
};

