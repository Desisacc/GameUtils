#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/ToAddFeatures/ClickableObject.h"

namespace MouseGameLayer {

	class Interactable : public GT::Component::ElementInContainer<Interactable, GT::Component::Positional, GT::Component::ObjectRenderable, GT::ObjectInSystemComponent, ClickableObject>
	{
	public:
		enum InteractableIds : size_t
		{
			ButtonOne
		};
	public:
		Interactable() = default;
		static void InitInteractables();
		void Init(const GT::Component::Positional::InitializerData& positionalData, GT::Component::ObjectRenderable::InitializerData& spriteSheetData, std::function<void()> onAction);

		void OnUpdate(Hazel::Timestep ts);
		void OnRender();

		void SetAction(std::function<void()> onAction)
		{
			m_OnAction = onAction;
		}
	private:
		std::function<void()> m_OnAction = nullptr;
	};

}