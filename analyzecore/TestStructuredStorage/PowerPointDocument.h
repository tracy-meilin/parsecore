#pragma once

class PowerPointDocument
{
public:
	PowerPointDocument();
	PowerPointDocument(shared_ptr<StructuredStorageReader> spReader);
	~PowerPointDocument();

	
	
public:
	shared_ptr<VirtualStream> spCurrentUserStream = nullptr;
};

