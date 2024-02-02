set_xmakever("2.8.0")
set_languages("c17", "cxx20")

target("glad")
    set_kind("static")
    add_files("$(projectdir)/octo/thirdparty/glad/src/**.c")

    add_includedirs("$(projectdir)/octo/thirdparty/glad/include", {public = true})