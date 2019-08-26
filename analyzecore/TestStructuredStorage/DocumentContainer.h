#pragma once
class DocumentContainer
	: public RegularContainer
{
public:
	DocumentContainer();
	DocumentContainer(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~DocumentContainer();

public:
	/// <summary>
	/// Collection of SlidePersistAtoms for master slides.
	/// </summary>
	vector<shared_ptr<SlidePersisAtom>> MasterPersistList;

	/// <summary>
	/// Collection of SlidePersistAtoms for notes slides.
	/// </summary>
	vector<shared_ptr<SlidePersisAtom>> NotesPersistList ;

	/// <summary>
	/// Collection of SlidePersistAtoms for regular slides.
	/// </summary>
	vector<shared_ptr<SlidePersisAtom>> SlidePersistList;

	shared_ptr<SlideListWithText> _spRegularSlideListWithText;

	shared_ptr<List> _spDocInfoListContainer;

};

