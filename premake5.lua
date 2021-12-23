workspace "DK"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "DK/vendor/GLFW/include"
IncludeDir["Glad"] = "DK/vendor/Glad/include"
IncludeDir["ImGui"] = "DK/vendor/imgui"

include "DK/vendor/GLFW"
include "DK/vendor/Glad"
include "DK/vendor/imgui"

project "DK"
	location "DK"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dkpch.h"
	pchsource "DK/src/dkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"DK_PLATFORM_WINDOWS",
			"DK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "DK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DK_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"DK/vendor/spdlog/include",
		"DK/src"
	}

	links
	{
		"DK"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"DK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "DK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DK_DIST"
		runtime "Release"
		optimize "On"