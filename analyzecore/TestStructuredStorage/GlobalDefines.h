#pragma once

namespace Common
{
	/// <summary>
	/// Constants used to identify sectors in fat, minifat and directory
	/// </summary>
	enum SectorId
	{
		MAXREGSECT = 0xFFFFFFFA,
		DIFSECT = 0xFFFFFFFC,
		FATSECT = 0xFFFFFFFD,
		ENDOFCHAIN = 0xFFFFFFFE,
		FREESECT = 0xFFFFFFFF,

		NOSTREAM = 0xFFFFFFFF
	};

	/// <summary>
	/// Size constants 
	/// </summary>
	enum Measures
	{
		DirectoryEntrySize = 128,
		HeaderSize = 512
	};

	/// <summary>
	/// Type of a directory entry
	/// </summary>
	enum DirectoryEntryType
	{
		STGTY_INVALID = 0,
		STGTY_STORAGE = 1,
		STGTY_STREAM = 2,
		STGTY_LOCKBYTES = 3,
		STGTY_PROPERTY = 4,
		STGTY_ROOT = 5
	};

	/// <summary>
	/// Color of a directory entry in the red-black-tree
	/// </summary>
	enum DirectoryEntryColor
	{
		DE_RED = 0,
		DE_BLACK = 1
	};

	enum SlideSizeType
	{
		OnScreen,
		LetterSizedPaper,
		A4Paper,
		Size35mm,
		Overhead,
		Banner,
		Custom
	};

	enum TextType
	{
		Title = 0,
		Body,
		Notes,
		Outline,
		Other,
		CenterBody,
		CenterTitle,
		HalfBody,
		QuarterBody
	};

	enum ParagraphMask
	{
		None = 0,

		/// <summary>
		/// A bit that specifies whether the bulletFlags field of the TextPFException structure that
		/// contains this PFMasks exists and whether bulletFlags.fHasBullet is valid.
		/// </summary>
		HasBullet = 1 << 0,

		/// <summary>
		/// A bit that specifies whether the bulletFlags field of the TextPFException structure that
		/// contains this PFMasks exists and whether bulletFlags.fBulletHasFont is valid.
		/// </summary>
		BulletHasFont = 1 << 1,

		/// <summary>
		/// A bit that specifies whether the bulletFlags field of the TextPFException structure that
		/// contains this PFMasks exists and whether bulletFlags. fBulletHasColor is valid.
		/// </summary>
		BulletHasColor = 1 << 2,

		/// <summary>
		/// A bit that specifies whether the bulletFlags field of the TextPFException structure that
		/// contains this PFMasks exists and whether bulletFlags.fBulletHasSize is valid.
		/// </summary>
		BulletHasSize = 1 << 3,

		BulletFlagsFieldExists = HasBullet | BulletHasFont | BulletHasColor | BulletHasSize,

		/// <summary>
		/// A bit that specifies whether the bulletFontRef field of the TextPFException structure that
		/// contains this PFMasks exists.
		/// </summary>
		BulletFont = 1 << 4,

		/// <summary>
		/// A bit that specifies whether the bulletColor field of the TextPFException structure that
		/// contains this PFMasks exists.
		/// </summary>
		BulletColor = 1 << 5,

		/// <summary>
		/// A bit that specifies whether the bulletSize field of the TextPFException structure that
		/// contains this PFMasks exists.
		/// </summary>
		BulletSize = 1 << 6,

		/// <summary>
		/// A bit that specifies whether the bulletChar field of the TextPFException structure that
		/// contains this PFMasks exists.
		/// </summary>
		BulletChar = 1 << 7,

		/// <summary>
		/// A bit that specifies whether the leftMargin field of the TextPFException structure that
		/// contains this PFMasks exists.
		/// </summary>
		LeftMargin = 1 << 8,

		unused9 = 1 << 9, // Bit 9 is reserved

		/// <summary>
		/// A bit that specifies whether the indent field of the TextPFException structure that
		/// contains this PFMasks exists.
		/// </summary>
		Indent = 1 << 10,

		/// <summary>
		/// A bit that specifies whether the textAlignment field of the TextPFException structure
		/// that contains this PFMasks exists.
		/// </summary>
		Align = 1 << 11,

		/// <summary>
		/// A bit that specifies whether the lineSpacing field of the TextPFException structure
		/// that contains this PFMasks exists.
		/// </summary>
		LineSpacing = 1 << 12,

		/// <summary>
		/// A bit that specifies whether the spaceBefore field of the TextPFException that
		/// contains this PFMasks exists.
		/// </summary>
		SpaceBefore = 1 << 13,

		/// <summary>
		/// A bit that specifies whether the spaceAfter field of the TextPFException
		/// structure that contains this PFMasks exists.
		/// </summary>
		SpaceAfter = 1 << 14,

		/// <summary>
		/// A bit that specifies whether the defaultTabSize field of the TextPFException
		/// structure that contains this PFMasks exists.
		/// </summary>
		DefaultTabSize = 1 << 15,

		/// <summary>
		/// A bit that specifies whether the fontAlign field of the TextPFException
		/// structure that contains this PFMasks exists.
		/// </summary>
		FontAlign = 1 << 16,

		/// <summary>
		/// A bit that specifies whether the wrapFlags field of the TextPFException
		/// structure that contains this PFMasks exists and whether wrapFlags.charWrap is valid.
		/// </summary>
		CharWrap = 1 << 17,

		/// <summary>
		/// A bit that specifies whether the wrapFlags field of the TextPFException
		/// structure that contains this PFMasks exists and whether wrapFlags.wordWrap is valid.
		/// </summary>
		WordWrap = 1 << 18,

		/// <summary>
		/// A bit that specifies whether the wrapFlags field of the TextPFException
		/// structure that contains this PFMasks exists and whether wrapFlags.overflow is valid.
		/// </summary>
		Overflow = 1 << 19,

		WrapFlagsFieldExists = CharWrap | WordWrap | Overflow,

		/// <summary>
		/// A bit that specifies whether the tabStops field of the TextPFException
		/// structure that contains this PFMasks exists.
		/// </summary>
		TabStops = 1 << 20,

		/// <summary>
		/// A bit that specifies whether the textDirection field of the TextPFException
		/// structure that contains this PFMasks exists.
		/// </summary>
		TextDirection = 1 << 21,

		unused22 = 1 << 22, // Bit 22 is reserved

		/// <summary>
		/// A bit that specifies whether the bulletBlipRef field of the TextPFException9
		/// structure that contains this PFMasks exists.
		/// </summary>
		BulletBlip = 1 << 23,

		/// <summary>
		/// A bit that specifies whether the bulletAutoNumberScheme field of the TextPFException9
		/// structure that contains this PFMasks exists.
		/// </summary>
		BulletScheme = 1 << 24,

		/// <summary>
		/// A bit that specifies whether the fBulletHasAutoNumber field of the TextPFException9
		/// structure that contains this PFMasks exists.
		/// </summary>
		BulletHasScheme = 1 << 25
	};
}

namespace Character {
	enum CharacterMask
	{
		None = 0,

		IsBold = 1 << 0,
		IsItalic = 1 << 1,
		IsUnderlined = 1 << 2,

		unused3 = 1 << 3, // Bit 3 is unused

		HasShadow = 1 << 4,
		HasAsianSmartQuotes = 1 << 5, //this should be fehint?

		unused6 = 1 << 6, // Bit 6 is unused

		HasHorizonNumRendering = 1 << 7, //this should be kumi?

		unused8 = 1 << 8, // Bit 8 is unused

		IsEmbossed = 1 << 9,

		unused10 = 1 << 10, // Bit 10 is unused
		unused11 = 1 << 11, // Bit 11 is unused
		unused12 = 1 << 12, // Bit 12 is unused
		unused13 = 1 << 13, // Bit 13 is unused
		unused14 = 1 << 14, // Bit 14 is unused
		unused15 = 1 << 15, // Bit 15 is unused

		// Bit 0 - 15 are used for marking style flag presence
		//StyleFlagsFieldPresent = 0xFFFF,

		TypefacePresent = 1 << 16,
		SizePresent = 1 << 17,
		ColorPresent = 1 << 18,
		PositionPresent = 1 << 19,

		unused20 = 1 << 20, // Bit 20 is unused

		FEOldTypefacePresent = 1 << 21,
		ANSITypefacePresent = 1 << 22,
		SymbolTypefacePresent = 1 << 23,
		unused24 = 1 << 24, // Bit 24 is unused
		unused25 = 1 << 25, // Bit 25 is unused
		pp11ext = 1 << 26,

		StyleFlagsFieldPresent = 0xFFFF,
	};
}

namespace Style{
	enum StyleMask
	{
		None = 0,

		IsBold = 1 << 0,
		IsItalic = 1 << 1,
		IsUnderlined = 1 << 2,

		// Bit 3 is unused

		HasShadow = 1 << 4,
		HasAsianSmartQuotes = 1 << 5, //this should be fehint?

		// Bit 6 is unused

		HasHorizonNumRendering = 1 << 7, //this should be kumi?

		// Bit 8 is unused

		IsEmbossed = 1 << 9,

		ExtensionNibble = 0xF << 10 // Bit 10 - 13

		// Bit 14 - 15 are unused
	};
}