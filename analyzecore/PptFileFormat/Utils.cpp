#include "stdafx.h"
#include "GlobalDefines.h"
#include "Utils.h"

const double MC_PER_EMU = 1587.5;

Utils::Utils()
{
}


Utils::~Utils()
{
}

signed long Utils::MasterCoordToEMU(signed long mc)
{
	return (signed long)(mc * MC_PER_EMU);
}

signed long Utils::EMUToMasterCoord(signed long emu)
{
	return (signed long)(emu / MC_PER_EMU);
}

bool Utils::BitmaskToBool(signed long value, signed long mask)
{
	return ((value & mask) == mask);
}

bool Utils::BitmaskToBool(unsigned long value, unsigned long mask)
{
	return ((value & mask) == mask);
}

bool Utils::BitmaskToBool(signed short value, signed short mask)
{
	return ((value & mask) == mask);
}

bool Utils::BitmaskToBool(unsigned short value, unsigned short mask)
{
	return ((value & mask) == mask);
}

std::wstring Utils::PlaceholderIdToXMLValue(OEPlaceHolderAtomSpace::PlaceholderEnum pid)
{
	wstring strResult = _T("");
	return strResult;
}

std::wstring Utils::GetPrstForShape(unsigned long shapeInstance)
{
	switch (shapeInstance)
	{
	case 0x0: //NotPrimitive
		return _T("");
	case 0x1: //Rectangle
		return _T("rect");
	case 0x2: //RoundRectangle
		return _T("roundRect");
	case 0x3: //ellipse
		return _T("ellipse");
	case 0x4: //diamond
		return _T("diamond");
	case 0x5: //triangle
		return _T("triangle");
	case 0x6: //right triangle
		return _T("rtTriangle");
	case 0x7: //parallelogram
		return _T("parallelogram");
	case 0x8: //trapezoid
		return _T("nonIsoscelesTrapezoid");
	case 0x9: //hexagon
		return _T("hexagon");
	case 0xA: //octagon
		return _T("octagon");
	case 0xB: //Plus
		return _T("mathPlus");
	case 0xC: //Star
		return _T("star5");
	case 0xD: //Arrow
	case 0xE: //ThickArrow
		return _T("rightArrow");
	case 0xF: //HomePlate
		return _T("homePlate");
	case 0x10: //Cube
		return _T("cube");
	case 0x11: //Balloon
		return _T("wedgeEllipseCallout");
	case 0x12: //Seal
		return _T("star16");
	case 0x13: //Arc
		return _T("curvedConnector2");
	case 0x14: //Line
		return _T("line");
	case 0x15: //Plaque
		return _T("plaque");
	case 0x16: //Cylinder
		return _T("can");
	case 0x17: //Donut
		return _T("donut");
	case 0x18: //TextSimple
	case 0x19: //TextOctagon
	case 0x1A: //TextHexagon
	case 0x1B: //TextCurve
	case 0x1C: //TextWave
	case 0x1D: //TextRing
	case 0x1E: //TextOnCurve
	case 0x1F: //TextOnRing
		return _T("");
	case 0x20: //StraightConnector1
		return _T("straightConnector1");
	case 0x21: //BentConnector2
		return _T("bentConnector2");
	case 0x22: //BentConnector3
		return _T("bentConnector3");
	case 0x23: //BentConnector4
		return _T("bentConnector4");
	case 0x24: //BentConnector5
		return _T("bentConnector5");
	case 0x25: //CurvedConnector2
		return _T("curvedConnector2");
	case 0x26: //CurvedConnector3
		return _T("curvedConnector3");
	case 0x27: //CurvedConnector4
		return _T("curvedConnector4");
	case 0x28: //CurvedConnector5
		return _T("curvedConnector5");
	case 0x29: //Callout1
		return _T("callout1");
	case 0x2A: //Callout2
		return _T("callout2");
	case 0x2B: //Callout3
		return _T("callout3");
	case 0x2C: //AccentCallout1
		return _T("accentCallout1");
	case 0x2D: //AccentCallout2
		return _T("accentCallout2");
	case 0x2E: //AccentCallout3
		return _T("accentCallout3");
	case 0x2F: //BorderCallout1
		return _T("borderCallout1");
	case 0x30: //BorderCallout2
		return _T("borderCallout2");
	case 0x31: //BorderCallout3
		return _T("borderCallout3");
	case 0x32: //AccentBorderCallout1
		return _T("accentBorderCallout1");
	case 0x33: //accentBorderCallout2
		return _T("accentBorderCallout2");
	case 0x34: //accentBorderCallout3
		return _T("accentBorderCallout3");
	case 0x35: //Ribbon
		return _T("ribbon");
	case 0x36: //Ribbon2
		return _T("ribbon2");
	case 0x37: //Chevron
		return _T("chevron");
	case 0x38: //Pentagon
		return _T("pentagon");
	case 0x39: //noSmoking
		return _T("noSmoking");
	case 0x3A: //Seal8
		return _T("star8");
	case 0x3B: //Seal16
		return _T("star16");
	case 0x3C: //Seal32
		return _T("star32");
	case 0x3D: //WedgeRectCallout
		return _T("wedgeRectCallout");
	case 0x3E: //WedgeRRectCallout
		return _T("wedgeRoundRectCallout");
	case 0x3F: //WedgeEllipseCallout
		return _T("wedgeEllipseCallout");
	case 0x40: //Wave
		return _T("wave");
	case 0x41: //FolderCorner
		return _T("foldedCorner");
	case 0x42: //LeftArrow
		return _T("leftArrow");
	case 0x43: //DownArrow
		return _T("downArrow");
	case 0x44: //UpArrow
		return _T("upArrow");
	case 0x45: //LeftRightArrow
		return _T("leftRightArrow");
	case 0x46: //UpDownArrow
		return _T("upDownArrow");
	case 0x47: //IrregularSeal1
		return _T("irregularSeal1");
	case 0x48: //IrregularSeal2
		return _T("irregularSeal2");
	case 0x49: //LightningBolt
		return _T("lightningBolt");
	case 0x4A: //Heart
		return _T("heart");
	case 0x4B: //PictureFrame
		//return "frame";
		return _T("rect");
	case 0x4C: //QuadArrow
		return _T("quadArrow");
	case 0x4D: //LeftArrowCallout
		return _T("leftArrowCallout");
	case 0x4E: //RightArrowCallout
		return _T("rightArrowCallout");
	case 0x4F: //UpArrowCallout
		return _T("upArrowCallout");
	case 0x50: //DownArrowCallout
		return _T("downArrowCallout");
	case 0x51: //LeftRightArrowCallout
		return _T("leftRightArrowCallout");
	case 0x52: //UpDownArrowCallout
		return _T("upDownArrowCallout");
	case 0x53: //QuadArrowCallout
		return _T("quadArrowCallout");
	case 0x54: //Bevel
		return _T("bevel");
	case 0x55: //LeftBracket
		return _T("leftBracket");
	case 0x56: //RightBracket
		return _T("rightBracket");
	case 0x57: //LeftBrace
		return _T("leftBrace");
	case 0x58: //RightBrace
		return _T("rightBrace");
	case 0x59: //LeftUpArrow
		return _T("leftUpArrow");
	case 0x5A: //BentUpArrow
		return _T("bentUpArrow");
	case 0x5B: //BentArrow
		return _T("bentArrow");
	case 0x5C: //Seal24
		return _T("star24");
	case 0x5D: //stripedRightArrow
		return _T("stripedRightArrow");
	case 0x5E: //notchedRightArrow
		return _T("notchedRightArrow");
	case 0x5F: //BlockArc
		return _T("blockArc");
	case 0x60: //SmileyFace
		return _T("smileyFace");
	case 0x61: //verticalScroll
		return _T("verticalScroll");
	case 0x62: //horizontalScroll
		return _T("horizontalScroll");
	case 0x63: //circularArrow                        
	case 0x64: //notchedCircularArrow
		return _T("circularArrow");
	case 0x65: //uturnArrow
		return _T("uturnArrow");
	case 0x66: //curvedRightArrow
		return _T("curvedRightArrow");
	case 0x67: //curvedLeftArrow
		return _T("curvedLeftArrow");
	case 0x68: //curvedUpArrow
		return _T("curvedUpArrow");
	case 0x69: //curvedDownArrow
		return _T("curvedDownArrow");
	case 0x6A: //CloudCallout
		return _T("cloudCallout");
	case 0x6B: //EllipseRibbon
		return _T("ellipseRibbon");
	case 0x6C: //EllipseRibbon2
		return _T("ellipseRibbon2");
	case 0x6D: //flowChartProcess
		return _T("flowChartProcess");
	case 0x6E: //flowChartDecision
		return _T("flowChartDecision");
	case 0x6F: //flowChartInputOutput
		return _T("flowChartInputOutput");
	case 0x70: //flowChartPredefinedProcess
		return _T("flowChartPredefinedProcess");
	case 0x71: //flowChartInternalStorage
		return _T("flowChartInternalStorage");
	case 0x72: //flowChartDocument
		return _T("flowChartDocument");
	case 0x73: //flowChartMultidocument
		return _T("flowChartMultidocument");
	case 0x74: //flowChartTerminator
		return _T("flowChartTerminator");
	case 0x75: //flowChartPreparation
		return _T("flowChartPreparation");
	case 0x76: //flowChartManualInput
		return _T("flowChartManualInput");
	case 0x77: //flowChartManualOperation
		return _T("flowChartManualOperation");
	case 0x78: //flowChartConnector
		return _T("flowChartConnector");
	case 0x79: //flowChartPunchedCard
		return _T("flowChartPunchedCard");
	case 0x7A: //flowChartPunchedTape
		return _T("flowChartPunchedTape");
	case 0x7B: //flowChartSummingJunction
		return _T("flowChartSummingJunction");
	case 0x7C: //flowChartOr
		return _T("flowChartOr");
	case 0x7D: //flowChartCollate
		return _T("flowChartCollate");
	case 0x7E: //flowChartSort
		return _T("flowChartSort");
	case 0x7F: //flowChartExtract
		return _T("flowChartExtract");
	case 0x80: //flowChartMerge
		return _T("flowChartMerge");
	case 0x81: //flowChartOfflineStorage
		return _T("flowChartOfflineStorage");
	case 0x82: //flowChartOnlineStorage
		return _T("flowChartOnlineStorage");
	case 0x83: //flowChartMagneticTape
		return _T("flowChartMagneticTape");
	case 0x84: //flowChartMagneticDisk
		return _T("flowChartMagneticDisk");
	case 0x85: //flowChartMagneticDrum
		return _T("flowChartMagneticDrum");
	case 0x86: //flowChartDisplay
		return _T("flowChartDisplay");
	case 0x87: //flowChartDelay
		return _T("flowChartDelay");
	case 0x88: //TextPlainText
	case 0x89: //TextStop
	case 0x8A: //TextTriangle
	case 0x8B: //TextTriangleInverted
	case 0x8C: //TextChevron
	case 0x8D: //TextChevronInverted
	case 0x8E: //TextRingInside
	case 0x8F: //TextRingOutside
	case 0x90: //TextArchUpCurve
	case 0x91: //TextArchDownCurve
	case 0x92: //TextCircleCurve
	case 0x93: //TextButtonCurve
	case 0x94: //TextArchUpPour
	case 0x95: //TextArchDownPour
	case 0x96: //TextCirclePout
	case 0x97: //TextButtonPout
	case 0x98: //TextCurveUp
	case 0x99: //TextCurveDown
	case 0x9A: //TextCascadeUp
	case 0x9B: //TextCascadeDown
	case 0x9C: //TextWave1
	case 0x9D: //TextWave2
	case 0x9E: //TextWave3
	case 0x9F: //TextWave4
	case 0xA0: //TextInflate
	case 0xA1: //TextDeflate
	case 0xA2: //TextInflateBottom
	case 0xA3: //TextDeflateBottom
	case 0xA4: //TextInflateTop
	case 0xA5: //TextDeflateTop
	case 0xA6: //TextDeflateInflate
	case 0xA7: //TextDeflateInflateDeflate
	case 0xA8: //TextFadeRight
	case 0xA9: //TextFadeLeft
	case 0xAA: //TextFadeUp
	case 0xAB: //TextFadeDown
	case 0xAC: //TextSlantUp
	case 0xAD: //TextSlantDown
	case 0xAE: //TextCanUp
	case 0xAF: //TextCanDown
		return _T("");
	case 0xB0: //flowchartAlternateProcess
		return _T("flowChartAlternateProcess");
	case 0xB1: //flowchartOffpageConnector
		return _T("flowChartOffpageConnector");
	case 0xB2: //Callout90
		return _T("callout1");
	case 0xB3: //AccentCallout90
		return _T("accentCallout1");
	case 0xB4: //BorderCallout90
		return _T("borderCallout1");
	case 0xB5: //AccentBorderCallout90
		return _T("accentBorderCallout1");
	case 0xB6: //LeftRightUpArrow
		return _T("leftRightUpArrow");
	case 0xB7: //Sun
		return _T("sun");
	case 0xB8: //Moon
		return _T("moon");
	case 0xB9: //BracketPair
		return _T("bracketPair");
	case 0xBA: //BracePair
		return _T("bracePair");
	case 0xBB: //Seal4
		return _T("star4");
	case 0xBC: //DoubleWave
		return _T("doubleWave");
	case 0xBD: //ActionButtonBlank
		return _T("actionButtonBlank");
	case 0xBE: //ActionButtonHome
		return _T("actionButtonHome");
	case 0xBF: //ActionButtonHelp
		return _T("actionButtonHelp");
	case 0xC0: //ActionButtonInformation
		return _T("actionButtonInformation");
	case 0xC1: //ActionButtonForwardNext
		return _T("actionButtonForwardNext");
	case 0xC2: //ActionButtonBackPrevious
		return _T("actionButtonBackPrevious");
	case 0xC3: //ActionButtonEnd
		return _T("actionButtonEnd");
	case 0xC4: //ActionButtonBeginning
		return _T("actionButtonBeginning");
	case 0xC5: //ActionButtonReturn
		return _T("actionButtonReturn");
	case 0xC6: //ActionButtonDocument
		return _T("actionButtonDocument");
	case 0xC7: //ActionButtonSound
		return _T("actionButtonSound");
	case 0xC8: //ActionButtonMovie
		return _T("actionButtonMovie");
	case 0xC9: //HostControl (do not use)
		return _T("");
	case 0xCA: //TextBox
		return _T("rect");
	default:
		return _T("");
	}
}

ImagePartSpace::ImageType Utils::GetImageType(unsigned long TypeCode)
{
	switch (TypeCode)
	{
	case 0xF01A:
		return ImagePartSpace::Emf;
	case 0xF01B:
		return ImagePartSpace::Wmf;
	case 0xF01D:
		return ImagePartSpace::Jpeg;
	case 0xF01E:
		return ImagePartSpace::Png;
	case 0xF01F: //DIP
		return ImagePartSpace::Bmp;
	case 0xF020:
		return ImagePartSpace::Tiff;
	default:
		return ImagePartSpace::Png;
	}
}
