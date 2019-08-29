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
}