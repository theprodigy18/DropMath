workspace "DropMath"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release"
	}

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Lib"
	location "Lib"
	kind "StaticLib"
	language "C"
	cdialect "C11"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.c",
	}
	includedirs
	{
		"%{prj.name}/include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		optimize "On"
		staticruntime "On"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
	}
	includedirs
	{
		"Lib/include"
	}
	links
	{
		"Lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		optimize "On"
		staticruntime "On"

