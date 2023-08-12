#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/ToAddFeatures/DragableObject.h"
#include "MouseGame/MouseGameObjects/ToAddFeatures/Button.h"

#include "MouseGameObjects/GlobalMouseGameObjects.h"
#include "MouseGame/MouseGameObjects/Map.h"
#include "MouseGame/MouseGameObjects/Room.h"

#include "MouseGame/MouseGameObjects/Inventory.h"
#include "MouseGame/MouseGameObjects/Item.h"
#include "MouseGame/MouseGameObjects/Door.h"

namespace MouseGameLayer {

	class MouseGameApp : public GT::BaseGameApp
	{
	public:
		virtual void Init() override;
		virtual void Destruct() override;
		virtual void OnUpdate(Hazel::Timestep ts) override;
		virtual void OnRender() override;
		virtual void OnEvent(Hazel::Event& e) override;
	private:
	private:
	};

}