#pragma once

#ifdef FG_PLATFORM_WINDOWS
#if FG_DYNAMIC_LINK
	#ifdef FG_BUILD_DLL
		#define FUGU_API __declspec(dllexport)
	#else
		#define FUGU_API __declspec(dllimport)
	#endif
#else
	#define FUGU_API 
#endif
#else
	#error Fugu only supports Windows!
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FC(x) std::bind(&x, this, std::placeholders::_1)

#ifdef FG_DEBUG
	#define FG_ASSERT(x, ...) { if(!(x)) {FG_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FG_CORE_ASSERT(x, ...) { if(!(x)) {FG_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FG_ASSERT(x, ...)
	#define FG_CORE_ASSERT(x, ...)
#endif

