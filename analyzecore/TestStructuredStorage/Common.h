#pragma once

// PowerPoint record types
#define PPT_PST_Document                        1000
#define PPT_PST_DocumentAtom                    1001
#define PPT_PST_SlideAtom                       1007
#define PPT_PST_NotesAtom                       1009
#define PPT_PST_Environment                     1010
#define PPT_PST_SlidePersistAtom                1011
#define PPT_PST_SSSlideInfoAtom                 1017
#define PPT_PST_VBAInfo                         1023
#define PPT_PST_VBAInfoAtom                     1024
#define PPT_PST_SSDocInfoAtom                   1025
#define PPT_PST_ExObjList                       1033
#define PPT_PST_ExObjListAtom					1034
#define PPT_PST_PPDrawingGroup                  1035
#define PPT_PST_PPDrawing                       1036
#define PPT_PST_GridSpacing10Atom               1037
#define PPT_PST_NamedShows                      1040
#define PPT_PST_NamedShow                       1041
#define PPT_PST_NamedShowSlides                 1042
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