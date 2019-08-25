#pragma once

class PowerPointDocument
{
public:
	PowerPointDocument();
	PowerPointDocument(shared_ptr<StructuredStorageReader> spReader);
	~PowerPointDocument();

private:
	void ScanDocumentSummaryInformation();
	
public:
	shared_ptr<VirtualStream> _spCurrentUserStream = nullptr;

	shared_ptr<VirtualStream> _spPicturesStream = nullptr;

	shared_ptr<VirtualStream> _spPowerpointDocumentStream = nullptr;

	shared_ptr<VirtualStream> _spDocumentSummaryInformationStream = nullptr;

	shared_ptr<CurrentUserAtom> _spCurrentUserAtom = nullptr;

	shared_ptr<UserEditAtom> _spUserEditAtom = nullptr;

	shared_ptr<Pictures> _spPictures = nullptr;
};

