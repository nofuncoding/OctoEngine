set_xmakever("2.8.0")

set_project("octo")
set_version("0.1.0-dev.0", {build = "%Y%m%d%H%M"})

set_languages("c17", "cxx20")
add_rules("mode.release", "mode.debug")

-- Packages

add_requires("spdlog ~1.13")

-- Targets

target("octo")
    set_kind("shared") -- to create a shared library
    add_defines("OCTO_BUILD_SHARED")

    add_packages("spdlog")

    -- build config (disabled now)
    -- add_includedirs("$(buildir)")
    -- add_configfiles("octo/src/BuildConfig.h.in")
    add_files("octo/src/*.cpp", "octo/src/**/*.cpp")

target("sandbox")
    add_deps("octo")
    add_packages("spdlog")
    add_files("sandbox/src/*.cpp")

    add_includedirs("$(projectdir)/octo/src")