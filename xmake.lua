add_rules("mode.debug", "mode.release")

-- =========================================================
-- Build options
-- =========================================================

option("avx2")
    set_default(true)
    set_showmenu(true)
    set_description("Enable AVX2 optimizations")
option_end()

-- =========================================================
-- Global configuration
-- =========================================================

set_languages("c++latest")

set_targetdir(is_mode("debug") and "Build/Debug" or "Build/Release")

-- IMPORTANT: correct CRT per configuration
if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
    set_runtimes("MDd")
    add_cxflags("/MDd")
    add_defines("_DEBUG")
else
    set_optimize("fastest")
    set_runtimes("MD")
    add_cxflags("/MD")
end

-- =========================================================
-- Dependencies
-- =========================================================

add_requires("minhook")
add_requires("nlohmann-json")
add_requires("libpng")
add_requires("zlib")
add_requires("imgui v1.91.9-docking", {
    configs = {
        win32 = true,
        dx12 = true,
        freetype = false
    },
    system = false
})

-- =========================================================
-- Target
-- =========================================================

target("Internal")
    set_kind("shared")

    -- AVX2 support
    if has_config("avx2") then
        add_vectorexts("avx2")
    end

    -- Precompiled header
    set_pcxxheader("Internal/PCH/pch.h")

    -- Includes
    add_includedirs("Internal", "Internal/PCH")

    -- Core files
    add_files("Internal/dllmain.cpp")
    add_files("Internal/PCH/pch.cpp")

    -- Utils
    add_files("Internal/Utils/Utils.cpp")
    add_files("Internal/Utils/Console/Console.cpp")
    add_files("Internal/Utils/Logging/Logging.cpp")

    -- Memory
    add_files("Internal/Memory/Memory.cpp")
    add_files("Internal/Memory/Windows/WindowsMemory.cpp")

    -- Systems
    add_files("Internal/Localization/Localization.cpp")
    add_files("Internal/Config/Config.cpp")

    -- Hooks
    add_files("Internal/Hooks/Renderer/D3D11Hooks.cpp")
    add_files("Internal/Hooks/Renderer/D3D12Hooks.cpp")
    add_files("Internal/Hooks/Renderer/RendererHooks.cpp")
    add_files("Internal/Hooks/WndProc/WndProcHooks.cpp")

    -- GUI
    add_files("Internal/GUI/GUI.cpp")
    add_files("Internal/GUI/Addons/imgui_addons.cpp")

    -- Features
    add_files("Internal/Features/*/*.cpp")

    -- Unreal SDK interfaces
    add_files("Internal/Interfaces/Unreal/SDK/Basic.cpp")
    add_files("Internal/Interfaces/Unreal/SDK/CoreUObject_functions.cpp")
    add_files("Internal/Interfaces/Unreal/SDK/Engine_functions.cpp")

    -- Packages
    add_packages("minhook", "imgui", "libpng", "zlib", "nlohmann-json")

    -- System libs
    add_syslinks("d3d11", "d3d12", "dxgi")