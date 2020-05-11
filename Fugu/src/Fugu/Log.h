#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fugu {

	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define FG_CORE_TRACE(...)      ::Fugu::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FG_CORE_INFO(...)       ::Fugu::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FG_CORE_WARN(...)       ::Fugu::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FG_CORE_ERROR(...)      ::Fugu::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FG_CORE_CRITICAL(...)   ::Fugu::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FG_TRACE(...)           ::Fugu::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FG_INFO(...)            ::Fugu::Log::GetClientLogger()->info(__VA_ARGS__)
#define FG_WARN(...)            ::Fugu::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FG_ERROR(...)           ::Fugu::Log::GetClientLogger()->error(__VA_ARGS__)
#define FG_CRITICAL(...)        ::Fugu::Log::GetClientLogger()->critical(__VA_ARGS__)