workspace "Fugu"
	architecture "x64"
	configurations 
	{ 
		"Debug", 
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Fugu/vendor/GLFW/include"
IncludeDir["Glad"] = "Fugu/vendor/Glad/include"
IncludeDir["ImGui"] = "Fugu/vendor/imgui"
IncludeDir["glm"] = "Fugu/vendor/glm"

startproject "Sandbox"

group "Dependencies"
	include "Fugu/vendor/GLFW"
	include "Fugu/vendor/Glad"
	include "Fugu/vendor/imgui"

group ""

project "Fugu"
	location "Fugu"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "fgpch.h"
	pchsource "%{prj.name}/src/fgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
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
			"FG_PLATFORM_WINDOWS",
			"FG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FG_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "FG_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "FG_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"	
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Fugu/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Fugu"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"FG_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "FG_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "FG_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "FG_DIST"
		runtime "Release"
		optimize "on"
