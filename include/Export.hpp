#pragma once


#if defined(_WIN32) && !defined(TIMECPP_STATIC)

	#if defined(TIMECPP_EXPORTS) 
	#define TIMECPP_API __declspec(dllexport) 
	#else 
	#define TIMECPP_API	__declspec(dllimport)
	#endif

#else

#define TIMECPP_API

#endif
