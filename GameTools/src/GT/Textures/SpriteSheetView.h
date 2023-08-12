#pragma once

#include "GT/Utils/Timer.h"
#include "GT/Textures/SpriteSheet.h"

namespace GT {

	class SpriteSheetView
	{
	public:
		SpriteSheetView() = default;
		void Init(size_t spriteSheetId, float timerForSprites);

		/*SpriteSheetView(const SpriteSheetView& other) noexcept
		{
			m_TimerForSprites = other.m_TimerForSprites;
			m_CurrentAnimationName = other.m_CurrentAnimationName;
			m_CurrentSpriteInAnimationIndex = m_CurrentSpriteInAnimationIndex;

			m_CacheCurrentAnimation = nullptr;
			m_CacheCurrentSprite = nullptr;
			m_CurrentAnimationHasChanged = true;
			m_CurrentSpriteHasChanged = true;
		}
		SpriteSheetView& operator=(const SpriteSheetView& other) noexcept
		{
			if (this == &other)
				return *this;

			m_TimerForSprites = other.m_TimerForSprites;
			m_CurrentAnimationName = other.m_CurrentAnimationName;
			m_CurrentSpriteInAnimationIndex = m_CurrentSpriteInAnimationIndex;

			m_CacheCurrentAnimation = nullptr;
			m_CacheCurrentSprite = nullptr;
			m_CurrentAnimationHasChanged = true;
			m_CurrentSpriteHasChanged = true;

			return *this;
		}
		SpriteSheetView(SpriteSheetView&& other) noexcept
		{
			m_SpriteSheet = other.m_SpriteSheet;
			other.m_SpriteSheet = nullptr;

			m_TimerForSprites = other.m_TimerForSprites;
			other.m_TimerForSprites = Timer();

			m_CurrentAnimationName = other.m_CurrentAnimationName;
			other.m_CurrentAnimationName.clear();

			m_CurrentSpriteInAnimationIndex = m_CurrentSpriteInAnimationIndex;
			other.m_CurrentSpriteInAnimationIndex = 0;

			m_CacheCurrentAnimation = nullptr;
			m_CacheCurrentSprite = nullptr;
			m_CurrentAnimationHasChanged = true;
			m_CurrentSpriteHasChanged = true;

			other.m_CacheCurrentAnimation = nullptr;
			other.m_CacheCurrentSprite = nullptr;
			other.m_CurrentAnimationHasChanged = true;
			other.m_CurrentSpriteHasChanged = true;
		}
		SpriteSheetView& operator=(SpriteSheetView&& other) noexcept
		{
			m_SpriteSheet = other.m_SpriteSheet;
			other.m_SpriteSheet = nullptr;

			m_TimerForSprites = other.m_TimerForSprites;
			other.m_TimerForSprites = Timer();

			m_CurrentAnimationName = other.m_CurrentAnimationName;
			other.m_CurrentAnimationName.clear();

			m_CurrentSpriteInAnimationIndex = m_CurrentSpriteInAnimationIndex;
			other.m_CurrentSpriteInAnimationIndex = 0;

			m_CacheCurrentAnimation = nullptr;
			m_CacheCurrentSprite = nullptr;
			m_CurrentAnimationHasChanged = true;
			m_CurrentSpriteHasChanged = true;

			other.m_CacheCurrentAnimation = nullptr;
			other.m_CacheCurrentSprite = nullptr;
			other.m_CurrentAnimationHasChanged = true;
			other.m_CurrentSpriteHasChanged = true;

			return *this;
		}*/

		void OnUpdate(Hazel::Timestep ts);
		void OnRender(Component::Positional& positional);
		void OnRender(Component::Positional& positional, Component::Rotational& rotational);

		void SetAnimation(const std::string& name, uint32_t indexOfStartingSprite = 0);

		size_t GetSpriteSheetId() const
		{
			return m_SpriteSheetId;
		}
		void SetIsRendered(bool isRendered)
		{
			m_IsRendered = isRendered;
		}
		bool GetIsRendered() const
		{
			return m_IsRendered;
		}
	private:
		SpriteSheet& GetSpriteSheet();
		const SpriteSheet& GetSpriteSheet() const;

		std::array<glm::vec2, 4> GetTextureCoordinatesFromCurrentSprite() const;

		const std::vector<SpriteSheet::Sprite>& GetCurrentAnimation() const;
		const SpriteSheet::Sprite& GetCurrentSpriteInAnimation() const;
	private:
		size_t m_SpriteSheetId = ObjectInSystemComponent::INVALID_ID;
		bool m_IsRendered = true;
		Timer m_TimerForSprites;

		std::string m_CurrentAnimationName;
		uint32_t m_CurrentSpriteInAnimationIndex = 0;

		mutable std::string m_CacheCurrentAnimationName;
		mutable size_t m_CacheCurrentSpriteIndex = std::numeric_limits<size_t>::max();
		mutable bool m_CurrentAnimationHasChanged = true;
		mutable bool m_CurrentSpriteHasChanged = true;
	};

}