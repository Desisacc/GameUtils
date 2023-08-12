#pragma once

#include "GT/Textures/SpriteSheet.h"
#include "GT/Textures/SpriteSheetView.h"

namespace GT {

	/*struct SpriteSheetRenderable
	{
		SpriteSheet SpriteSheetOfObject;
		SpriteSheetView SpriteSheetViewOfObject;

		SpriteSheetRenderable() = default;
		SpriteSheetRenderable(const SpriteSheetRenderable& other) noexcept
		{
			SpriteSheetOfObject = other.SpriteSheetOfObject;
			SpriteSheetViewOfObject = other.SpriteSheetViewOfObject;
			SpriteSheetViewOfObject.m_SpriteSheet = &SpriteSheetOfObject;
		}
		SpriteSheetRenderable& operator=(const SpriteSheetRenderable& other) noexcept
		{
			if (this == &other)
				return *this;

			SpriteSheetOfObject = other.SpriteSheetOfObject;
			SpriteSheetViewOfObject = other.SpriteSheetViewOfObject;
			SpriteSheetViewOfObject.m_SpriteSheet = &SpriteSheetOfObject;
			return *this;
		}
		SpriteSheetRenderable(SpriteSheetRenderable&& other) noexcept
		{
			SpriteSheetOfObject = std::move(other.SpriteSheetOfObject);
			SpriteSheetViewOfObject = std::move(other.SpriteSheetViewOfObject);
			SpriteSheetViewOfObject.m_SpriteSheet = &SpriteSheetOfObject;
		}
		SpriteSheetRenderable& operator=(SpriteSheetRenderable&& other) noexcept
		{
			SpriteSheetOfObject = std::move(other.SpriteSheetOfObject);
			SpriteSheetViewOfObject = std::move(other.SpriteSheetViewOfObject);
			SpriteSheetViewOfObject.m_SpriteSheet = &SpriteSheetOfObject;
			return *this;
		}
	};*/

}