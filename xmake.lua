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

    octo_src = "octo/src/"

    add_includedirs(octo_src)
    set_pcxxheader(octo_src .. "octo_pch.h")
    add_files(octo_src .. "**.cpp")

    if is_mode("debug") then 
        add_defines("OCTO_DEBUG")
    elseif is_mode("release") then 
        add_defines("OCTO_RELEASE")
    --[[elseif is_mode("dist") then
        add_defines("OCTO_DIST")]]
    end

    after_build(function (target) 
        os.cp("$(projectdir)/LICENSE", target:targetdir())
        os.cp("$(projectdir)/COPYRIGHT", target:targetdir())
    end)

target("sandbox")
    add_deps("octo")
    add_packages("spdlog")
    add_files("sandbox/src/*.cpp")

    add_includedirs("$(projectdir)/octo/src")