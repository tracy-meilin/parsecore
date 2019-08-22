#pragma once

class DirectoryTree
{
public:
	DirectoryTree();
	DirectoryTree(shared_ptr<Fat> spFat, shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler);
	~DirectoryTree();

	unsigned long GetMiniStreamStart();

	unsigned __int64 GetSizeOfMiniStream();

private:
	void Init(unsigned long startSector);

	void GetAllDirectoryEntriesRecursive(unsigned long sid, wstring path);

	shared_ptr<DirectoryEntry> ReadDirectoryEntry(unsigned long sid, wstring path);

	void SeekToDirectoryEntry(unsigned long sid);

	shared_ptr<DirectoryEntry> GetDirectoryEntry(unsigned long sid);

private:
	shared_ptr<Fat> _spFat = nullptr;
	shared_ptr<Header> _spHeader = nullptr;
	shared_ptr<InputHandler> _spFileHandler = nullptr;
	vector<unsigned long> _sectorsUsedByDirectory;
	vector<shared_ptr<DirectoryEntry>> _directoryEntries;
};

