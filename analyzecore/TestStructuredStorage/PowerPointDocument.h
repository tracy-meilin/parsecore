#pragma once

class PowerPointDocument
{
public:
	PowerPointDocument();
	PowerPointDocument(shared_ptr<StructuredStorageReader> spReader);
	~PowerPointDocument();

private:
	void ScanDocumentSummaryInformation();

	void ConstructPersistObjectDirectory();

	vector<shared_ptr<PersistDirectoryAtom>> FindLivePersistDirectoryAtoms();

	template<typename T>
	shared_ptr<T> GetPersistObject(unsigned long persistId);

	void IdentifyDocumentPersistObject();

	void IdentifyMasterPersistObjects();

	void IdentifySlidePersistObjects();
	
public:
	shared_ptr<VirtualStream> _spCurrentUserStream = nullptr;

	shared_ptr<VirtualStream> _spPicturesStream = nullptr;

	shared_ptr<VirtualStream> _spPowerpointDocumentStream = nullptr;

	shared_ptr<VirtualStream> _spDocumentSummaryInformationStream = nullptr;

	shared_ptr<CurrentUserAtom> _spCurrentUserAtom = nullptr;

	shared_ptr<UserEditAtom> _spLastUserEdit = nullptr;

	shared_ptr<Pictures> _spPictures = nullptr;

	/// <summary>
	/// The DocumentContainer record for this document.
	/// </summary>
	shared_ptr<DocumentContainer> _spDocumentRecord = nullptr;

	/// <summary>
	/// List of all main (regular) master records for this document.
	/// </summary>
	vector<shared_ptr<MainMaster>> m_vecMainMasterRecords;

	/// <summary>
	/// List of all notes master records for this document.
	/// </summary>
	vector<shared_ptr<Note>> m_vecNotesMasterRecords;

	/// <summary>
	/// List of all notes master records for this document.
	/// </summary>
	vector<shared_ptr<Handout>> m_vecHandoutMasterRecords;

	/// <summary>
	/// List of title master records for this document.
	/// </summary>
	vector<shared_ptr<Slide>> m_vecTitleMasterRecords;

	/// <summary>
	/// Dictionary used for finding MasterRecords (title / main masters) by master id.
	/// </summary>
	map<unsigned long, shared_ptr<Slide>> m_mapMasterRecordsById;

	map<unsigned long, unsigned long> _mapPersistObjectDirectory;

	/// <summary>
	/// List of all slide records for this document.
	/// </summary>
	vector<shared_ptr<Slide>> m_vecSlideRecords;

	/// <summary>
	/// List of all note records for this document.
	/// </summary>
	vector<shared_ptr<Note>> m_vecNoteRecords;
};

template<typename T>
shared_ptr<T>
PowerPointDocument::GetPersistObject(unsigned long persistId)
{
	auto& ele = this->_mapPersistObjectDirectory.find(persistId);
	if (ele == this->_mapPersistObjectDirectory.end())
		return nullptr;

	unsigned long offset = ele->second;
	this->_spPowerpointDocumentStream->Seek(offset, SEEK_SET);
	return dynamic_pointer_cast<T>(RecordFactory::GetInstance()->CreateRecord(_spPowerpointDocumentStream));
}

