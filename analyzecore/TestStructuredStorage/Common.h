#pragma once

// PowerPoint record types
#define PPT_PST_Document                        1000
#define PPT_PST_DocumentAtom                    1001
#define PPT_PST_EndDocument						1002
#define PPT_PST_Slide							1006
#define PPT_PST_SlideAtom                       1007
#define PPT_PST_NotesAtom                       1009
#define PPT_PST_Environment                     1010
#define PPT_PST_SlidePersistAtom                1011
#define PPT_PST_MainMaster						1016
#define PPT_PST_SSSlideInfoAtom                 1017
#define PPT_PST_VBAInfo                         1023
#define PPT_PST_VBAInfoAtom                     1024
#define PPT_PST_SSDocInfoAtom                   1025
#define PPT_PST_ExObjList                       1033
#define PPT_PST_ExObjListAtom					1034
#define PPT_PST_PPDrawingGroup                  1035
#define PPT_PST_PPDrawing                       1036
#define PPT_PST_GridSpacing10Atom               1037
#define PPT_PST_THEME							1038
#define PPT_PST_ColorMappingAtom				1039
#define PPT_PST_NamedShows                      1040
#define PPT_PST_NamedShow                       1041
#define PPT_PST_NamedShowSlides                 1042
#define PPT_PST_OriginalMainMasterId			1052
#define PPT_PST_RoundTripContentMasterInfo12	1054
#define PPT_PST_RoundTripOArtTextStyles12		1059
#define PPT_PST_List                            2000
#define PPT_PST_FontCollection                  2005
#define PPT_PST_SoundCollection                 2020
#define PPT_PST_Sound                           2022
#define PPT_PST_SoundData                       2023
#define PPT_PST_ColorSchemeAtom                 2032

// these atoms first was seen in ppt2000 in a private Tag atom
#define PPT_PST_ExtendedBuGraContainer          2040    // consist of 4041
#define PPT_PST_ExtendedBuGraAtom               2041    // the instance of this atom indices the current graphic

#define PPT_PST_ExObjRefAtom                    3009
#define PPT_PST_OEPlaceholderAtom               3011
#define PPT_PST_OutlineTextRefAtom              3998
#define PPT_PST_TextHeaderAtom                  3999
#define PPT_PST_TextCharsAtom                   4000
#define PPT_PST_StyleTextPropAtom               4001
#define PPT_PST_TxMasterStyleAtom               4003
#define PPT_PST_TxCFStyleAtom					4004
#define PPT_PST_TxPFStyleAtom                   4005
#define PPT_PST_TextRulerAtom                   4006
#define PPT_PST_TextBytesAtom                   4008
#define PPT_PST_TxSIStyleAtom                   4009
#define PPT_PST_TextSpecInfoAtom                4010

// these atoms first was seen in ppt2000 in a private Tag atom
#define PPT_PST_ExtendedParagraphAtom           4012
#define PPT_PST_ExtendedParagraphMasterAtom     4013
#define PPT_PST_ExtendedPresRuleContainer       4014    // consist of 4012, 4015,
#define PPT_PST_ExtendedParagraphHeaderAtom     4015    // the instance of this atom indices the current presobj
// the first sal_uInt32 in this atom indices the current slideId
#define PPT_PST_TextDefaults9Atom               4016

#define PPT_PST_FontEntityAtom                  4023
#define PPT_PST_CString                         4026
#define PPT_PST_ExOleObjAtom                    4035
#define PPT_PST_SrKinsoku                       4040
#define PPT_PST_ExEmbed                         4044
#define PPT_PST_ExHyperlinkAtom                 4051
#define PPT_PST_ExHyperlink                     4055
#define PPT_PST_SlideNumberMCAtom               4056
#define PPT_PST_HeadersFooters                  4057
#define PPT_PST_HeadersFootersAtom              4058
#define PPT_PST_TxInteractiveInfoAtom           4063
#define PPT_PST_MasterText                      4068
#define PPT_PST_RecolorInfoAtom                 4071
#define PPT_PST_ExControl                       4078
#define PPT_PST_SlideListWithText               4080
#define PPT_PST_AnimationInfoAtom               4081
#define PPT_PST_InteractiveInfo                 4082
#define PPT_PST_InteractiveInfoAtom             4083
#define PPT_PST_UserEditAtom                    4085
#define PPT_PST_CurrentUserAtom                 4086
#define PPT_PST_DateTimeMCAtom                  4087
#define PPT_PST_GenericDateMCAtom               4088
#define PPT_PST_HeaderMCAtom                    4089
#define PPT_PST_FooterMCAtom                    4090
#define PPT_PST_ExMediaAtom                     4100
#define PPT_PST_ExVideo                         4101
#define PPT_PST_ExAviMovie                      4102
#define PPT_PST_ExMCIMovie                      4103
#define PPT_PST_ExMidiAudio						4109
#define PPT_PST_AnimationInfo                   4116
#define PPT_PST_RTFDateTimeMCAtom               4117
#define PPT_PST_ProgTags                        5000
#define PPT_PST_ProgBinaryTag                   5002
#define PPT_PST_BinaryTagData                   5003
#define PPT_PST_PersistPtrIncrementalBlock      6002

// these atoms first was seen in ppt2000 in a private Tag atom
#define PPT_PST_PresentationAdvisorFlags9Atom   6010
#define PPT_PST_HtmlDocInfo9Atom                6011


#define PPT_PST_HashCodeAtom                    11008
#define PPT_PST_BuildList                       11010
#define PPT_PST_Comment10                       12000
#define PPT_PST_CommentAtom10                   12001
#define PPT_PST_CommentIndex10                  12004
#define PPT_PST_SlideFlags10Atom                12010
#define PPT_PST_SlideTime10Atom                 12011
#define PPT_PST_DocToolbarStates10Atom          14001

#define DFF_PST_TextHeaderAtom              3999
#define DFF_PST_TextCharsAtom               4000
#define DFF_PST_TextBytesAtom               4008
#define DFF_PST_ExOleObjStg                 4113

//      Record Name                 FBT-Value Instance                  Contents                                                          Wrd Exl Ppt Ver

#define DFF_msofbtDggContainer      0xF000 //                           per-document data                                                  X   X   X
#define   DFF_msofbtDgg             0xF006 //                           an FDGG and several FIDCLs                                         X   X   X   0
#define   DFF_msofbtCLSID           0xF016 //                           the CLSID of the application that put the data on the clipboard    C   C   C   0
#define   DFF_msofbtOPT             0xF00B // count of properties       the document-wide default shape properties                         X   X   X   3
#define   DFF_msofbtColorMRU        0xF11A // count of colors           the colors in the MRU swatch                                       X   X   X   0
#define   DFF_msofbtSplitMenuColors 0xF11E // count of colors           the colors in the top-level split menus                            X   X   X   0
#define   DFF_msofbtBstoreContainer 0xF001 // count of BLIPs            all images in the document (JPEGs, metafiles, etc.)                X   X   X
#define     DFF_msofbtBSE           0xF007 // BLIP type                 an FBSE (one per BLIP)                                             X   X   X   2
#define     DFF_msofbtBlipFirst     0xF018 //                           range of fbts reserved for various kinds of BLIPs                  X   X   X
#define     DFF_msofbtBlipLast      0xF117 //                           range of fbts reserved for various kinds of BLIPs                  X   X   X

#define DFF_msofbtDgContainer       0xF002 //                           per-sheet/page/slide data                                          X   X   X
#define   DFF_msofbtDg              0xF008 // drawing ID                an FDG                                                             X   X   X   0
#define   DFF_msofbtRegroupItems    0xF118 // count of regroup entries  several FRITs                                                      X   X   X   0
#define   DFF_msofbtColorScheme     0xF120 // count of colors           the colors of the source host's color scheme                           C   C   0
#define   DFF_msofbtOPT_121         0xF121 // count of properties       the document-wide default shape properties                         X   X   X   3
#define   DFF_msofbtOPT_122         0xF122 // count of properties       the document-wide default shape properties                         X   X   X   3
#define   DFF_msofbtSpgrContainer   0xF003 //                           several SpContainers, the first of which is the group shape itself X   X   X
#define   DFF_msofbtSpContainer     0xF004 //                           a shape                                                            X   X   X
#define     DFF_msofbtSpgr          0xF009 //                           an FSPGR; only present if the shape is a group shape               X   X   X   1
#define     DFF_msofbtSp            0xF00A // shape type                an FSP                                                             X   X   X   2
#define     DFF_msofbtTextbox       0xF00C //                           RTF text                                                           C   C   C   0
#define     DFF_msofbtClientTextbox 0xF00D // host-defined              the text in the textbox, in host-defined format                    X   X   X
#define     DFF_msofbtAnchor        0xF00E //                           a RECT, in 100000ths of an inch                                    C   C   C   0
#define     DFF_msofbtChildAnchor   0xF00F //                           a RECT, in units relative to the parent group                      X   X   X   0
#define     DFF_msofbtClientAnchor  0xF010 // host-defined              the location of the shape, in a host-defined format                X   X   X
#define     DFF_msofbtClientData    0xF011 // host-defined              host-specific data                                                 X   X   X
#define     DFF_msofbtOleObject     0xF11F //                           a serialized IStorage for an OLE object                            C   C   C   0
#define     DFF_msofbtDeletedPspl   0xF11D //                           an FPSPL; only present in top-level deleted shapes                 X           0
#define     DFF_msofbtUDefProp      0xF122 //                           range of fbts reserved for various kinds of BLIPs                  X   X   X
#define   DFF_msofbtSolverContainer 0xF005 // count of rules            the rules governing shapes                                         X   X   X
#define     DFF_msofbtConnectorRule 0xF012 //                           an FConnectorRule                                                      X   X   1
#define     DFF_msofbtAlignRule     0xF013 //                           an FAlignRule                                                      X   X   X   0
#define     DFF_msofbtArcRule       0xF014 //                           an FARCRU                                                          X   X   X   0
#define     DFF_msofbtClientRule    0xF015 // host-defined              host-defined
#define     DFF_msofbtCalloutRule   0xF017 //                           an FCORU      
#define DFF_msofbtBitmapBlip_1D						0xF01D
#define DFF_msofbtBitmapBlip_1E						0xF01E
#define DFF_msofbtBitmapBlip_1F						0xF01F
#define DFF_msofbtBitmapBlip_20						0xF020
#define DFF_msofbtBitmapBlip_21						0xF021

namespace Common{
	template<typename T>
	static T bytes2T(unsigned char *bytes)
	{
		T res = 0;
		int n = sizeof(T);
		memcpy(&res, bytes, n);
		return res;
	}

	template<typename T>
	static unsigned char * T2bytes(T u)
	{
		int n = sizeof(T);
		unsigned char* b = new unsigned char[n];
		memcpy(b, &u, n);
		return b;
	}

	wstring Utf8ToUnicode(const string& strUtf8);

	wstring Utf8ToUnicode(const char* pszUtf8);

	string UnicodeToUtf8(const wstring& strUnicode);

	string UnicodeToUtf8(const wchar_t* pszUnicode);
}