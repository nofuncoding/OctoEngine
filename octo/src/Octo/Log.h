#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Octo {
    
    class OCTO_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Log macros
#define OCTO_CORE_TRACE(...)    ::Octo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OCTO_CORE_INFO(...)     ::Octo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OCTO_CORE_WARN(...)     ::Octo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OCTO_CORE_ERROR(...)    ::Octo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OCTO_CORE_FATAL(...)    ::Octo::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define OCTO_TRACE(...)         ::Octo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OCTO_INFO(...)          ::Octo::Log::GetClientLogger()->info(__VA_ARGS__)
#define OCTO_WARN(...)          ::Octo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OCTO_ERROR(...)         ::Octo::Log::GetClientLogger()->error(__VA_ARGS__)
#define OCTO_FATAL(...)         ::Octo::Log::GetClientLogger()->fatal(__VA_ARGS__)