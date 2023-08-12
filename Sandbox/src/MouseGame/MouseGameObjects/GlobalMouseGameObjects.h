#pragma once

#include "MouseGame/MouseGameObjects/Map.h"

namespace MouseGameLayer {

	class GlobalMouseGameObjects
	{
	public:
		GlobalMouseGameObjects() = delete;

		enum SpriteSheetIds : size_t
		{
			MainRoom_SSI = 1, LivingRoom_SSI, Kitchen_SSI,

			InventoryIcon_SSI, InventoryBackground_SSI,

			Hammer_SSI, MasterKey_SSI,

			ButtonOne_SSI
		};

		static bool ButtonOneHasBeenPressed;
		static bool ButtonTwoHasBeenPressed;

	};

}