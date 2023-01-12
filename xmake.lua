add_rules("mode.debug", "mode.release")

package("ads")
    set_sourcedir(path.join(os.scriptdir(), "3rdparty/Qt-Advanced-Docking-System"))
    set_policy("package.install_always", true)
    on_install(function (package)
        print(get_config("mode")) 
        package:config_set("mode",get_config("mode"))
        package:config_set("debug", is_mode("debug"))
        print(package:configs())
        import("package.tools.xmake").install(package)
        os.cp("src/*.h",package:installdir("include")) 
    end)
package_end()  

add_requires("ads")
add_requires("nlohmann_json", {alias="json"})
add_includedirs("src/", "src/headers")

target("Tests")
    add_packages("ads")
    add_packages("json")
    add_rules("qt.widgetapp")
    add_headerfiles("src/headers/*.h")
    add_files("src/sources/*.cpp")
    -- for automoc
    add_files("src/headers/*.h")
    -- for autouic
    add_files("src/ui/*.ui")
    -- for autorcc
    add_files("src/*.qrc")
    add_frameworks("QtMultiMedia","QtGui")
    -- assets
    before_build(function (target)
        os.cp("$(project_dir)/src/assets", target:targetdir().."/")
    end
    )
    before_install(function (target)
        os.cp("$(project_dir)/src/assets", target:installdir().."bin/")
    end
    )
