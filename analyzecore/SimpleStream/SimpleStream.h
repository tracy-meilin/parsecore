#pragma once

#if defined(_WIN32)
#if defined(SIMPLESTREAM_EXPORTS)
#define SimpleStream_API __declspec(dllexport)
#else
#define SimpleStream_API __declspec(dllimport)
#endif
#endif

#undef BEGIN_SIMPLE_STREAM_SPCE 
#define BEGIN_SIMPLE_STREAM_SPCE  namespace simple{

#undef END_SIMPLE_STREAM_SPCE
#define END_SIMPLE_STREAM_SPCE }


