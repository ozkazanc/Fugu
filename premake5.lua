workspace "Fugu"
	architecture "x64"
	configurations 
	{ 
		"Debug", 
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Fugu"
	location "Fugu"
	kind "SharedLib"
	language "C++"
	
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
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"FG_PLATFORM_WINDOWS",
			"FG_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FG_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "FG_RELEASE"
		optimize "On"
	
	filter "configurations:Dist"
		defines "FG_DIST"
		optimize "On"

project "Sandbox"	
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"FG_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "FG_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "FG_RELEASE"
		optimize "On"
	
	filter "configurations:Dist"
		defines "FG_DIST"
		optimize "On"