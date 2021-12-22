#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace DK {

	class DK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){return s_CoreLogger;}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){return s_ClientLogger;}
	

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// Core log macros
#define DK_CORE_TRACE(...)	::DK::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DK_CORE_INFO(...)	::DK::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DK_CORE_WARN(...)	::DK::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DK_CORE_ERROR(...)	::DK::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DK_CORE_FATAL(...)	::DK::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define DK_TRACE(...)	::DK::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DK_INFO(...)	::DK::Log::GetClientLogger()->info(__VA_ARGS__)
#define DK_WARN(...)	::DK::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DK_ERROR(...)	::DK::Log::GetClientLogger()->error(__VA_ARGS__)
#define DK_FATAL(...)	::DK::Log::GetClientLogger()->fatal(__VA_ARGS__)




