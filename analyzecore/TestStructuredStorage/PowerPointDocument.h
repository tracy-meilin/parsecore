#pragma once

class PowerPointDocument
{
public:
	PowerPointDocument();
	PowerPointDocument(shared_ptr<StructuredStorageReader> spReader);
	~PowerPointDocument();

	
	
public:
	shared_ptr<VirtualStream> _spCurrentUserStream = nullptr;

	shared_ptr<VirtualStream> _spPicturesStream = nullptr;

	shared_ptr<CurrentUserAtom> _spCurrentUserAtom = nullptr;
};

