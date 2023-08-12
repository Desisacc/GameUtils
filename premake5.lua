include "vendor/premake/premake_customization/solution_items.lua"

workspace "CustomProjects"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	solution_items
	{
		".editorconfig.txt"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/vendor/HazelTutorial/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/vendor/HazelTutorial/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/vendor/HazelTutorial/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/vendor/yaml-cpp/include"
IncludeDir["spdlog"] = "%{wks.location}/vendor/HazelTutorial/vendor/spdlog/include"
IncludeDir["hazel"] = "%{wks.location}/vendor/HazelTutorial/src"

group "Dependencies"
	include "vendor/premake"
	include "vendor/GLFW"
	include "vendor/Glad"
	include "vendor/imgui"
	include "vendor/yaml-cpp"
	include "vendor/HazelTutorial"
group ""
				
include "GameTools"
include "Sandbox"