#pragma once
class SlideListWithText 
	: public RegularContainer
{
public:
	SlideListWithText();
	SlideListWithText(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~SlideListWithText();

	shared_ptr<TextHeaderAtom> FindTextHeaderForOutlineTextRef(shared_ptr<OutlineTextRefAtom> spAtom);

	
public:
	/// <summary>
	/// List of all SlidePersistAtoms of this SlideListWithText.
	/// </summary>
	vector<shared_ptr<SlidePersistAtom>> m_vecSlidePersistAtoms;

	/// <summary>
	/// This dictionary manages a list of TextHeaderAtoms for each SlidePersistAtom.
	/// 
	/// Text of placeholders can appear in the SlideListWithText record.
	/// This dictionary is used for associating such text records with the slide they appear on.
	/// </summary>
	map<shared_ptr<SlidePersistAtom>, vector<shared_ptr<TextHeaderAtom>>> m_mapSlideToPlaceholderTextHeaders;
};

