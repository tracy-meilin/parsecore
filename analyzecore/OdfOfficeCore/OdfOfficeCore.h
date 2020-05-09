#pragma once

#pragma once

#if defined(_WIN32)
#if defined(ODFOFFICECORE_EXPORTS)
#define ODFOfficeCore_API __declspec(dllexport)
#else
#define ODFOfficeCore_API __declspec(dllimport)
#endif
#endif