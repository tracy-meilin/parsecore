#pragma once

class PptFileFormat_API SSlideLayoutAtom
{
public:
	SSlideLayoutAtom();
	SSlideLayoutAtom(shared_ptr<BinaryReader> spBinaryReader);
	~SSlideLayoutAtom();

public:
	/// <summary>
	/// A SlideLayoutType that specifies a hint to the user interface which
	/// slide layout exists on the corresponding slide.
	/// 
	/// A slide layout specifies the type and number of placeholder shapes
	/// on a slide. A placeholder shape is specified as an OfficeArtSpContainer
	/// ([MS-ODRAW] section 2.2.14) that contains a PlaceholderAtom record
	/// with a pos field not equal to 0xFFFFFFFF. The placementId field of the
	/// PlaceholderAtom record specifies the placeholder shape type.
	/// </summary>
	SSlideLayoutAtomSpace::SlideLayoutType Geom;

	/// <summary>
	/// An array of PlaceholderEnum enumeration values that specifies
	/// a hint to the user interface which placeholder shapes exist on
	/// the corresponding slide.
	/// 
	/// The count of items in the array MUST be 8.
	/// </summary>
	vector<OEPlaceHolderAtomSpace::PlaceholderEnum> m_vecPlaceholderTypes;
};

