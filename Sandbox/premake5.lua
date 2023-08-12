project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"%{wks.location}/GameTools/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.hazel}"

		--"%{IncludeDir.entt}",
		--"%{IncludeDir.yaml_cpp}",
	}

	links
	{
		--"HazelTutorial",
		"GameTools"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "GT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GT_DIST"
		runtime "Release"
		optimize "on"