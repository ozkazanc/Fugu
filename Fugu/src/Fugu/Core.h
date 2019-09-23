#pragma once

#ifdef FG_PLATFORM_WINDOWS
	#ifdef FG_BUILD_DLL
		#define FUGU_API __declspec(dllexport)
	#else
		#define FUGU_API __declspec(dllimport)
	#endif
#else
	#error Fugu only supports Windows!
#endif

