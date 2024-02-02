set_xmakever("2.8.0")

set_project("octo")
set_version("0.1.0-dev.0", {build = "%Y%m%d%H%M"})

set_languages("c17", "cxx20")
add_rules("mode.release", "mode.debug")

-- Packages

package("glfw")
    set_homepage("https://www.glfw.org/")
    set_description("GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.")
    set_license("zlib")

    add_urls("https://github.com/glfw/glfw/archive/$(version).tar.gz",
             "https://github.com/glfw/glfw.git")
    add_versions("3.3.2", "98768e12e615fbe9f3386f5bbfeb91b5a3b45a8c4c77159cef06b1f6ff749537")
    add_versions("3.3.4", "cc8ac1d024a0de5fd6f68c4133af77e1918261396319c24fd697775a6bc93b63")
    add_versions("3.3.5", "32fdb8705784adfe3082f97e0d41e7c515963e977b5a14c467a887cf0da827b5")
    add_versions("3.3.6", "ed07b90e334dcd39903e6288d90fa1ae0cf2d2119fec516cf743a0a404527c02")
    add_versions("3.3.7", "fd21a5f65bcc0fc3c76e0f8865776e852de09ef6fbc3620e09ce96d2b2807e04")
    add_versions("3.3.8", "f30f42e05f11e5fc62483e513b0488d5bceeab7d9c5da0ffe2252ad81816c713")
    add_versions("3.3.9", "a7e7faef424fcb5f83d8faecf9d697a338da7f7a906fc1afbc0e1879ef31bd53")

    add_configs("glfw_include", {description = "Choose submodules enabled in glfw", default = "none", type = "string", values = {"none", "vulkan", "glu", "glext", "es2", "es3"}})

    if is_plat("linux") then
        add_extsources("apt::libglfw3-dev", "pacman::glfw-x11")
    end

    add_deps("cmake")
    add_deps("opengl", {optional = true})
    if is_plat("macosx") then
        add_frameworks("Cocoa", "IOKit")
    elseif is_plat("windows") then
        add_syslinks("user32", "shell32", "gdi32")
    elseif is_plat("mingw") then
        add_syslinks("gdi32")
    elseif is_plat("linux") then
        -- TODO: add wayland support
        add_deps("libx11", "libxrandr", "libxrender", "libxinerama", "libxfixes", "libxcursor", "libxi", "libxext")
        add_syslinks("dl", "pthread")
        add_defines("_GLFW_X11")
    end

    on_load(function (package)
        package:add("defines", "GLFW_INCLUDE_" .. package:config("glfw_include"):upper())
    end)

    on_install("macosx", "windows", "linux", "mingw", function (package)
        local configs = {"-DGLFW_BUILD_DOCS=OFF", "-DGLFW_BUILD_TESTS=OFF", "-DGLFW_BUILD_EXAMPLES=OFF"}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        if package:is_plat("windows") then
            table.insert(configs, "-DUSE_MSVC_RUNTIME_LIBRARY_DLL=" .. (package:runtimes():startswith("MT") and "OFF" or "ON"))
        end
        if package:is_plat("linux") then
            import("package.tools.cmake").install(package, configs, {packagedeps = {"libxrender", "libxfixes", "libxext", "libx11"}})
        else
            import("package.tools.cmake").install(package, configs)
        end
    end)

    on_test(function (package)
        assert(package:check_csnippets({test = [[
            void test() {
                glfwInit();
                glfwTerminate();
            }
        ]]}, {configs = {languages = "c11"}, includes = "GLFW/glfw3.h"}))
    end)
package_end()

add_requires("spdlog ~1.13")
add_requires("glfw ~3.3")

-- Targets

target("octo")
    set_kind("shared") -- to create a shared library
    add_defines("OCTO_BUILD_SHARED")

    add_packages("spdlog", "glfw")

    -- build config (disabled now)
    -- add_includedirs("$(buildir)")
    -- add_configfiles("octo/src/BuildConfig.h.in")

    octo_src = "octo/src/"

    add_includedirs(octo_src)
    set_pcxxheader(octo_src .. "octo_pch.h")
    add_files(octo_src .. "**.cpp")

    if is_mode("debug") then 
        add_defines("OCTO_DEBUG", "OCTO_ENABLE_ASSERTS")
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