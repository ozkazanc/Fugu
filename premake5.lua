workspace "Fugu"
	architecture "x64"
	configurations 
	{ 
		"Debug", 
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Fugu/vendor/GLFW/include"
IncludeDir["Glad"] = "Fugu/vendor/Glad/include"
IncludeDir["ImGui"] = "Fugu/vendor/imgui"

startproject "Sandbox"

include "Fugu/vendor/GLFW"
include "Fugu/vendor/Glad"
include "Fugu/vendor/imgui"

project "Fugu"
	location "Fugu"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "fgpch.h"
	pchsource "%{prj.name}/src/fgpch.cpp"

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
			"FG_PLATFORM_WINDOWS",
			"FG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FG_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "FG_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "FG_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"	
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Fugu/vendor/spdlog/include",
		"Fugu/src"
	}

	links
	{
		"Fugu"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"FG_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "FG_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "FG_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "FG_DIST"
		runtime "Release"
		optimize "On"