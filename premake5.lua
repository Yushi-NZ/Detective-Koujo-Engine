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
IncludeDir["glm"] = "DK/vendor/glm"

include "DK/vendor/GLFW"
include "DK/vendor/Glad"
include "DK/vendor/imgui"

project "DK"
	location "DK"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dkpch.h"
	pchsource "DK/src/dkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DK_PLATFORM_WINDOWS",
			"DK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "DK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DK_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"DK/src",
		"DK/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"DK"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"DK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DK_DIST"
		runtime "Release"
		optimize "on"
