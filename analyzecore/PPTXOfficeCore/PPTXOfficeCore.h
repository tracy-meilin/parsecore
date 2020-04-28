#pragma once

#if defined(_WIN32)
#if defined(PPTXOFFICECORE_EXPORTS)
#define PPTXOfficeCore_API __declspec(dllexport)
#else
#define PPTXOfficeCore_API __declspec(dllimport)
#endif
#endif