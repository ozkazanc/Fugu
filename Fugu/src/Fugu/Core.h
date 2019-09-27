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

#define BIT(x) (1 << x)

#ifdef FG_DEBUG
	#define FG_ASSERT(x, ...) { if(!(x)) {FG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FG_CORE_ASSERT(x, ...) { if(!(x)) {FG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FG_ASSERT(x, ...)
	#define FG_CORE_ASSERT(x, ...)
#endif

