#pragma once

class DirectoryEntry
	: public AbstractDirectoryEntry
{
public:
	DirectoryEntry();
	DirectoryEntry(shared_ptr<Header> spHeader, shared_ptr<InputHandler> spFileHandler, unsigned long sid, wstring path);
	~DirectoryEntry();

private:
	void ReadDirectoryEntry();

private:
	shared_ptr<InputHandler> _spFileHandler = nullptr;
	shared_ptr<Header> _spHeader = nullptr;
};

