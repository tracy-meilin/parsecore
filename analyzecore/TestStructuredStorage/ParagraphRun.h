#pragma once


class ParagraphRun
{
public:
	ParagraphRun();
	ParagraphRun(shared_ptr<BinaryReader> spBinaryReader, bool noIndentField);
	~ParagraphRun();

	bool GetBulletFlagsFieldPresent()
	{
		return (this->mask & Common::BulletFlagsFieldExists) != 0;
	}

	bool GetBulletCharPresent()
	{
		return (this->mask & Common::BulletChar) != 0;
	}

	bool GetBulletFontPresent()
	{
		return (this->mask & Common::BulletFont) != 0;
	}

	bool GetBulletHasFont()
	{
		return (this->mask & Common::BulletHasFont) != 0;
	}

	bool GetBulletSizePresent()
	{
		return (this->mask & Common::BulletSize) != 0;
	}

	bool GetBulletHasSize()
	{
		return (this->mask & Common::BulletHasSize) != 0;
	}

	bool GetBulletColorPresent()
	{
		return (this->mask & Common::BulletColor) != 0;
	}

	bool GetBulletHasColor()
	{
		return (this->mask & Common::BulletHasColor) != 0;
	}

	bool GetAlignmentPresent()
	{
		return (this->mask & Common::Align) != 0;
	}

	bool GetLineSpacingPresent()
	{
		return (this->mask & Common::LineSpacing) != 0;
	}

	bool GetSpaceBeforePresent()
	{
		return (this->mask & Common::SpaceBefore) != 0;
	}

	bool GetSpaceAfterPresent()
	{
		return (this->mask & Common::SpaceAfter) != 0;
	}

	bool GetLeftMarginPresent()
	{
		return (this->mask & Common::LeftMargin) != 0;
	}

	bool GetIndentPresent()
	{
		return (this->mask & Common::Indent) != 0;
	}

	bool GetDefaultTabSizePresent()
	{
		return (this->mask & Common::DefaultTabSize) != 0;
	}

	bool GetTabStopsPresent()
	{
		return (this->mask & Common::TabStops) != 0;
	}

	bool GetFontAlignPresent()
	{
		return (this->mask & Common::FontAlign) != 0;
	}

	bool GetLineBreakFlagsFieldPresent()
	{
		return (this->mask & Common::WrapFlagsFieldExists) != 0;
	}

	bool GetTextDirectionPresent()
	{
		return (this->mask & Common::TextDirection) != 0;
	}

public:
	vector<shared_ptr<TabStop>> m_vecTabStop;

	unsigned long Length;
	unsigned short IndentLevel;
	Common::ParagraphMask mask;

	unsigned short BulletFlags;
	wchar_t BulletChar;
	unsigned short BulletTypefaceIdx;
	signed short BulletSize;
	shared_ptr<GrColorAtom> _spBulletColor = nullptr;

	signed short Alignment;
	signed short LineSpacing;
	signed short SpaceBefore;
	signed short SpaceAfter;
	signed short LeftMargin;
	signed short Indent;
	signed short DefaultTabSize;
	unsigned short FontAlign;
	unsigned short LineBreakFlags;
	unsigned short _TextDirectioin;
};

