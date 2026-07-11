add_rules("mode.debug", "mode.release")

-- =========================================================
-- Build options
-- =========================================================

option("avx2")
    set_default(true)
    set_showmenu(true)
    set_description("Enable AVX2 optimizations")
option_end()

option("avx512")
    set_default(false)
    set_showmenu(true)
    set_description("Enable AVX512 optimizations");
option_end()

option("avec")
    set_default(false)
    set_showmenu(true)
    set_description("Enable all vector extensions")
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
add_requires("nlohmann_json")
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

target("Payday3-Internal_V2")
    set_kind("shared")

    -- AVX2 support
    if has_config("avx2") then
        add_vectorexts("avx2")
    end

    if has_config("avx512") then
        add_vectorexts("avx512")
    end

    if has_config("avec") then 
        add_vectorexts("sse", "sse2", "sse4.2", "avx", "avx2", "avx512")
    end

    -- Precompiled header
    set_pcxxheader("Payday3-Internal_V2/PCH/pch.h")

    -- Includes
    add_includedirs("Payday3-Internal_V2", "Payday3-Internal_V2/PCH")

    -- Core files
    add_files("Payday3-Internal_V2/dllmain.cpp")
    add_files("Payday3-Internal_V2/PCH/pch.cpp")

    -- Utils
    add_files("Payday3-Internal_V2/Utils/Utils.cpp")
    add_files("Payday3-Internal_V2/Utils/Console/Console.cpp")
    add_files("Payday3-Internal_V2/Utils/Logging/Logging.cpp")

    -- Memory
    add_files("Payday3-Internal_V2/Memory/Memory.cpp")
    add_files("Payday3-Internal_V2/Memory/Windows/WindowsMemory.cpp")

    -- Systems
    add_files("Payday3-Internal_V2/Localization/Localization.cpp")
    add_files("Payday3-Internal_V2/Config/Config.cpp")

    -- Hooks
    add_files("Payday3-Internal_V2/Hooks/Renderer/D3D11Hooks.cpp")
    add_files("Payday3-Internal_V2/Hooks/Renderer/D3D12Hooks.cpp")
    add_files("Payday3-Internal_V2/Hooks/Renderer/RendererHooks.cpp")
    add_files("Payday3-Internal_V2/Hooks/WndProc/WndProcHooks.cpp")

    -- GUI
    add_files("Payday3-Internal_V2/GUI/GUI.cpp")
    add_files("Payday3-Internal_V2/GUI/Addons/imgui_addons.cpp")

    -- Features
    add_files("Payday3-Internal_V2/Features/*/*.cpp")

    -- Unreal SDK interfaces
    add_files("Payday3-Internal_V2/Interfaces/Unreal/SDK/Basic.cpp")
    add_files("Payday3-Internal_V2/Interfaces/Unreal/SDK/CoreUObject_functions.cpp")
    add_files("Payday3-Internal_V2/Interfaces/Unreal/SDK/Engine_functions.cpp")
    add_files("Payday3-Internal_V2/Interfaces/Unreal/SDK/Starbreeze_functions.cpp")

    -- Packages
    add_packages("minhook", "imgui", "libpng", "zlib", "nlohmann_json")

    -- System libs
    add_syslinks("d3d11", "d3d12", "dxgi")