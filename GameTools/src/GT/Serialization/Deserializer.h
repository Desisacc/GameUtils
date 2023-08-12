#pragma once

#include <string>

#include "GT/Utils/GlobalData.h"
#include "GT/Components/Components.h"

// Filepath: C:\\Users\\olga_\\Desktop\\CustomProjects\\Sandbox\\assets\\levels\\lol.txt 

namespace GT {

	class Deserializer
	{
	public:
		Deserializer() = delete;

		template<typename ... Components>
		static void DeserializeComponents(std::vector<std::string>& lines, Components& ... components)
		{
			lines.erase(lines.begin()); // Deleting '{'
			DeserializeNextComponent<Components...>(lines, components...);
			lines.erase(lines.begin()); // Deleting '}'
		}

		static void DeserializeGlobalData(std::vector<std::string>& lines)
		{
			GlobalData::SetWindowSize(DeserializeVector2<uint32_t>(lines[1]));
			GlobalData::SetMapSize(DeserializeVector2<uint32_t>(lines[2]));

			// Deleting everything between the "[]"
			constexpr uint32_t linesInGlobalData = 4;
			lines.erase(lines.begin(), lines.begin() + linesInGlobalData);
		}
	private:
		// Functions to go through all elements
		template<typename ... Components> static void DeserializeNextComponent(std::vector<std::string>& lines, Components& ... components);
		template<typename First, typename ... Components> static void DeserializeNextComponent(std::vector<std::string>& lines, First& first, Components& ... components)
		{
			// Find all lines of component and move them into another vector and erase the remanent unusable objects from the original vector
			std::vector<std::string> linesToPass;
			size_t linesInComponent = 1;
			for (linesInComponent; lines[linesInComponent][0] == '\t' && linesInComponent < lines.size(); linesInComponent++);
			linesToPass.reserve(linesInComponent);

			for (size_t currentLineIndex = 0; currentLineIndex < linesInComponent; currentLineIndex++)
				linesToPass.emplace_back(std::move(lines[currentLineIndex]));
			lines.erase(lines.begin(), lines.begin() + linesInComponent);

			Deserialize<First>(linesToPass, first);
			DeserializeNextComponent<Components...>(lines, components...);
		}
		template<> static void DeserializeNextComponent(std::vector<std::string>& lines) {}

		// All deserializer functions need to be explicitly specialized
		template<typename Component> static void Deserialize(const std::vector<std::string>& lines, Component& component);

		// Utility functions
		template<typename Dst> static Dst DeserializeVariable(const std::string& line)
		{
			return static_cast<Dst>(std::atof(line.substr(1).c_str()));
		}
		template<typename Dst> static Vector2<Dst> DeserializeVector2(const std::string& line)
		{
			const size_t separatorIndex = line.find('|');
			const std::string firstNumStr = line.substr(0, separatorIndex);
			const std::string secondNumStr = line.substr(separatorIndex + 1);

			return { static_cast<Dst>(std::atof(firstNumStr.c_str())), static_cast<Dst>(std::atof(secondNumStr.c_str())) };
		}
		static Rectangle DeserializeRectangle(const std::string& one, const std::string& two)
		{
			const Vector2<float> position = DeserializeVector2<float>(one);
			const Vector2<float> size = DeserializeVector2<float>(two);
			return { position, size };
		}
	};

	// These specializations can also be included inside the class
	template<> inline void Deserializer::Deserialize<Component::Positional>(const std::vector<std::string>& lines, Component::Positional& component)
	{
		Assert(lines[0].find("Positional") != std::string::npos, "Not a positional component!");

		component.m_Rectangle = DeserializeRectangle(lines[1], lines[2]);
		component.m_Depth = DeserializeVariable<float>(lines[3]);
	}
	template<> inline void Deserializer::Deserialize<Component::Directional>(const std::vector<std::string>& lines, Component::Directional& component)
	{
		Assert(lines[0].find("Directional") != std::string::npos, "Not a directional component!");

		component.m_Speed = DeserializeVector2<float>(lines[1]);
		component.m_SpeedFromLastUpdate = DeserializeVector2<float>(lines[2]);
		component.m_PreviousRectangle = DeserializeRectangle(lines[3], lines[4]);
	}

}