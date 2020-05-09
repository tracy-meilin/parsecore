#ifndef _DEBUGPRINTF_H_
#define _DEBUGPRINTF_H_

#define REPORT_LEVEL_NONE			0
#define REPORT_LEVEL_ERROR			1
#define REPORT_LEVEL_WARRNING	2
#define REPORT_LEVEL_DEBUG			3

#ifdef _DEBUG
	#define REPORTLEVEL  REPORT_LEVEL_DEBUG
#else
	#define REPORTLEVEL  REPORT_LEVEL_WARRNING
#endif

void debugprintf(wchar_t* format, ...);

#if(REPORTLEVEL > REPORT_LEVEL_NONE)
#define ReportError(...)			debugprintf(__VA_ARGS__)
#else
	#define ReportError
#endif

#if(REPORTLEVEL > REPORT_LEVEL_ERROR)
#define ReportWarrning(...)		debugprintf(__VA_ARGS__)
#else
	#define ReportWarrning
#endif 

#if(REPORTLEVEL > REPORT_LEVEL_WARRNING)
#define REPORT_DEBUG(...)			debugprintf(__VA_ARGS__)
#else
	#define REPORT_DEBUG
#endif

#endif