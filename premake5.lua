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
	language "C++"
	cppdialect "C++11"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.inl",
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
		
	filter "action:vs*"
		buildoptions { "/Zc:__cplusplus" }

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

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DM_RELEASE"
		optimize "On"
		staticruntime "On"
	
	filter "action:vs*"
		buildoptions { "/Zc:__cplusplus" }

