#pragma once

#include <map>
#include <Hazel.h>

#include "GT/Utils/Vectors.h"
#include "GT/Utils/Timer.h"

#include "GT/Components/LocalComponent.h"
#include "GT/ObjectSystems/ObjectInSystem.h"

namespace GT {

	namespace Component
	{
		struct Positional;
		struct Rotational;
	}

	class SpriteSheet : public Component::ElementInContainer<SpriteSheet, ObjectInSystemComponent>
	{
	public:
		struct InitializerForSpriteSheet
		{
			struct AnimationPairInfo
			{
				std::string AnimationName;
				uint32_t IndexForAnimation = std::numeric_limits<uint32_t>::max();
				uint32_t NumberOfSpritesInAnimation = 0;

				AnimationPairInfo() = default;
				AnimationPairInfo(const std::string& animationName, uint32_t indexForAnimation, uint32_t numberOfSpritesInAnimation = 0) noexcept
					: AnimationName(animationName), IndexForAnimation(indexForAnimation), NumberOfSpritesInAnimation(numberOfSpritesInAnimation) {}
			};

			std::string Filepath;
			std::vector<AnimationPairInfo> AnimationsInfo;
			// If left as zero the spriteSheetSize will be set to the entirety of the texture
			Vector2<float> SpriteSize = { 0.0f, 0.0f };
		};

		struct Sprite 
		{
			Vector2<uint32_t> TextureCoordsIndex = { 0, 0 };

			Sprite(Vector2<uint32_t> textureCoordsIndex) noexcept
				: TextureCoordsIndex(textureCoordsIndex) {}
			Sprite(uint32_t tilePositionX, uint32_t tilePositionY) noexcept
				: TextureCoordsIndex({ tilePositionX, tilePositionY }) {}
		};
	public:
		SpriteSheet() = default;
		void Init(const std::string& filepath, Vector2<float> spriteSize);
		void Init(const Hazel::Ref<Hazel::Texture2D>& texture, Vector2<float> spriteSize);
		void Init(const InitializerForSpriteSheet& spriteSheetData);
		
		SpriteSheet(const SpriteSheet& other) noexcept;
		SpriteSheet& operator=(const SpriteSheet& other) noexcept;
		SpriteSheet(SpriteSheet&& other) noexcept;
		SpriteSheet& operator=(SpriteSheet&& other) noexcept;

		void OnRender(const Component::Positional& positional, const std::array<glm::vec2, 4>& texCoords);
		void OnRender(const Component::Positional& positional, const Component::Rotational& rotational, const std::array<glm::vec2, 4>& texCoords);

		// Animations must be placed in rows, index goes from bottom (index 0) to top (max index)
		void AddAnimation(const std::string& name, uint32_t indexOfAnimationInSpriteSheet, uint32_t numberOfSpritesInAnimation = 0);
	private:
		Hazel::Ref<Hazel::Texture2D> m_Texture = nullptr;
		Vector2<float> m_SpriteSize = { 0.0f, 0.0f };
		Vector2<float> m_SpriteSheetSize = { 0.0f, 0.0f };
		Vector2<uint32_t> m_SpriteSheetSizeInTiles = { 0, 0 };

		std::unordered_map<std::string, std::vector<Sprite>> m_Animations;

		friend class SpriteSheetView;
	};

}