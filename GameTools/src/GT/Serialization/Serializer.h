#pragma once

#include <string>
#include <imgui.h>

#include "GT/Utils/GlobalData.h"
#include "GT/Components/Components.h"

namespace GT {

	class Serializer
	{
	public:
		Serializer() = delete;

		template<typename ... Components> 
		static std::string SerializeComponents(Components&& ... components)
		{
			return "{\n" + SerializeNextComponent(std::forward<Components>(components)...) + "}\n";
		}

		static std::string SerializeGlobalData()
		{
			return std::string("[") +
				"\n\t" + SerializeVector2(GlobalData::GetWindowSize()) +
				"\n\t" + SerializeVector2(GlobalData::GetMapSize())
				+ "\n]\n";
		}

		template<typename T> static std::string GetTypeName(const T& typeVar)
		{
			return GetTypeName<T>();
		}
		template<typename T> static std::string GetTypeName()
		{
			std::string typeName = typeid(T).name();
			size_t typeNameIndex = typeName.find_last_of("::");

			if (typeNameIndex == std::string::npos)
			{
				typeNameIndex = typeName.find_last_of(" ");

				if (typeNameIndex == std::string::npos)
					return typeName;
			}

			return typeName.substr(typeNameIndex + 1);
		}

		template<typename T, typename ... Args> static void ImGuiInfo(T& component, Args ... args);
	private:
		// Functions to go through all elements
		template<typename ... Components> static std::string SerializeNextComponent(Components&& ... components);
		template<typename First, typename ... Components> static std::string SerializeNextComponent(First&& first, Components&& ... components)
		{
			// Types need to be inferred and not deduced
			return Serialize(std::forward<First>(first)) + SerializeNextComponent(std::forward<Components>(components)...);
		}
		template<> static std::string SerializeNextComponent()
		{
			return "";
		}

		// All serializer functions need to be explicitly specialized
		template<typename ComponentType> static std::string Serialize(const ComponentType& component);

		// Utility functions
		template<typename Src, typename Dest = Src> static std::string SerializeVariable(const Src& variable)
		{
			return std::to_string(static_cast<Dest>(variable));
		}
		template<typename Src, typename Dest = Src> static std::string SerializeVector2(const Vector2<Src>& typeVector)
		{
			const Vector2<Dest> vector = { static_cast<Dest>(typeVector.x), static_cast<Dest>(typeVector.y) };
			return std::to_string(vector.x) + '|' + std::to_string(vector.y);
		}
		static std::string SerializeRectangle(const Rectangle& rectangle)
		{
			return SerializeVector2<float, int>(rectangle.Position) +
				"\n\t" + SerializeVector2<float, int>(rectangle.Size);
		}
	};

	// These specializations can also be included inside the class
	template<> inline std::string Serializer::Serialize<Component::Positional>(const Component::Positional& component)
	{
		return std::string("Positional") +
			"\n\t" + SerializeRectangle(component.GetRectangle()) +
			"\n\t" + SerializeVariable(component.GetDepth())
			+ '\n';
	}
	template<> inline std::string Serializer::Serialize<Component::Directional>(const Component::Directional& component)
	{
		return std::string("Directional") +
			"\n\t" + SerializeVector2<float, int>(component.GetSpeed()) +
			"\n\t" + SerializeVector2<float, int>(component.GetSpeedFromLastUpdate()) +
			"\n\t" + SerializeRectangle(component.GetPreviousRectangle())
			+ '\n';
	}

	template<> inline void Serializer::ImGuiInfo<Component::Positional, Vector2<float>>(Component::Positional& positional, Vector2<float> sizeMinMax)
	{
		ImGui::Text("Positional:");
		ImGui::DragFloat("Size X", &positional.m_Rectangle.Size.x, 1.0f, sizeMinMax[0], sizeMinMax[1], "%.3f", ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat("Size Y", &positional.m_Rectangle.Size.y, 1.0f, sizeMinMax[0], sizeMinMax[1], "%.3f", ImGuiSliderFlags_AlwaysClamp);
	}
	template<> inline void Serializer::ImGuiInfo<Component::Directional, Vector2<float>>(Component::Directional& directional, Vector2<float> speedMinMax)
	{
		ImGui::Text("Directional:");
		ImGui::DragFloat("Speed X", &directional.m_Speed.x, 1.0f, speedMinMax[0], speedMinMax[1], "%.3f", ImGuiSliderFlags_AlwaysClamp);
		ImGui::DragFloat("Speed Y", &directional.m_Speed.y, 1.0f, speedMinMax[0], speedMinMax[1], "%.3f", ImGuiSliderFlags_AlwaysClamp);
	}

}