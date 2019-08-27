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

	shared_ptr<SlidePersistAtom> SlidePersistAtomForSlideWithIdx(unsigned long idx);

public:
	/// <summary>
	/// Collection of SlidePersistAtoms for master slides.
	/// </summary>
	vector<shared_ptr<SlidePersistAtom>> MasterPersistList;

	/// <summary>
	/// Collection of SlidePersistAtoms for notes slides.
	/// </summary>
	vector<shared_ptr<SlidePersistAtom>> NotesPersistList ;

	/// <summary>
	/// Collection of SlidePersistAtoms for regular slides.
	/// </summary>
	vector<shared_ptr<SlidePersistAtom>> SlidePersistList;

	shared_ptr<SlideListWithText> _spRegularSlideListWithText;

	shared_ptr<List> _spDocInfoListContainer;

};

