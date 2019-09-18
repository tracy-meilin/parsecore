#pragma once

#if defined(_WIN32)
#if defined(OFFICECORE_EXPORTS)
#define OfficeCore_API __declspec(dllexport)
#else
#define OfficeCore_API __declspec(dllimport)
#endif
#endif