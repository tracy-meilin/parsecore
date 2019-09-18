#pragma once

#if defined(_WIN32)
#if defined(PPTFILEFORMAT_EXPORTS)
#define PptFileFormat_API __declspec(dllexport)
#else
#define PptFileFormat_API __declspec(dllimport)
#endif
#endif
