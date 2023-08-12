project "GameTools"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gtpch.h"
	pchsource "src/gtpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
		--"%{wks.location}/vendor/stb_image/**.h",
		--"%{wks.location}/vendor/stb_image/**.cpp",
		--"%{wks.location}/vendor/glm/glm/**.hpp",
		--"%{wks.location}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.hazel}"

		--"%{IncludeDir.spdlog}",
		--"%{IncludeDir.GLFW}",
		--"%{IncludeDir.Glad}",
		--"%{IncludeDir.stb_image}",
	}

	links
	{
		--"GLFW",
		--"Glad",
		--"ImGui",
		--"yaml-cpp",
		--"opengl32.lib",

		"HazelTutorial"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "GT_DEBUG"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GT_RELEASE"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GT_DIST"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"