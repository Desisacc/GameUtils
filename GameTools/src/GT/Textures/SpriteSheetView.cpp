#include "gtpch.h"
#include "GT/Textures/SpriteSheetView.h"

#include "GT/ObjectSystems/SpriteSheetSystem.h"

namespace GT {

	void SpriteSheetView::Init(size_t spriteSheetId, float timerForSprites)
	{
		m_SpriteSheetId = spriteSheetId;
		m_TimerForSprites.SetNewWaitingTime(timerForSprites);
	}

	void SpriteSheetView::OnUpdate(Hazel::Timestep ts)
	{
		// When waiting time is set to 0.0f, there won't be any updates
		if (!m_TimerForSprites.GetWaitingTime())
			return;

		if (m_TimerForSprites.TimerHasEnded(ts))
		{
			const size_t numberOfSpritesInAnimation = GetCurrentAnimation().size();
			m_CurrentSpriteInAnimationIndex++;
			m_CurrentSpriteInAnimationIndex %= numberOfSpritesInAnimation;
			m_CurrentSpriteHasChanged = true;
		}
	}

	void SpriteSheetView::OnRender(Component::Positional& positional) 
	{
		if (!m_IsRendered)
			return;

		const std::array<glm::vec2, 4> texCoords = GetTextureCoordinatesFromCurrentSprite();

		SpriteSheet& spriteSheet = GetSpriteSheet();
		spriteSheet.OnRender(positional, texCoords);
	}

	void SpriteSheetView::OnRender(Component::Positional& positional, Component::Rotational& rotational)
	{
		if (!m_IsRendered)
			return;

		const std::array<glm::vec2, 4> texCoords = GetTextureCoordinatesFromCurrentSprite();

		SpriteSheet& spriteSheet = GetSpriteSheet();
		spriteSheet.OnRender(positional, rotational, texCoords);
	}

	void SpriteSheetView::SetAnimation(const std::string& name, uint32_t indexOfStartingSprite)
	{
		SpriteSheet& spriteSheet = GetSpriteSheet();

		Assert(spriteSheet.m_Animations.find(name) != spriteSheet.m_Animations.end(), "Animation {0}, does not exist!", name.c_str());
		m_CurrentAnimationName = name;
		m_CurrentAnimationHasChanged = true;

		const size_t numberOfSpritesInCurrentAnimation = GetCurrentAnimation().size();
		Assert(indexOfStartingSprite < numberOfSpritesInCurrentAnimation, "indexOfStartingSprite is out of bounds! :{0}", indexOfStartingSprite);
		m_CurrentSpriteInAnimationIndex = indexOfStartingSprite;
	}

	// Private fuctions //

	SpriteSheet& SpriteSheetView::GetSpriteSheet()
	{
		return LoadingSystem<SpriteSheet>::GetLoadedObject(m_SpriteSheetId);
	}
	const SpriteSheet& SpriteSheetView::GetSpriteSheet() const
	{
		return LoadingSystem<SpriteSheet>::GetLoadedObject(m_SpriteSheetId);
	}

	std::array<glm::vec2, 4> SpriteSheetView::GetTextureCoordinatesFromCurrentSprite() const
	{
		const SpriteSheet& spriteSheet = GetSpriteSheet();
		std::array<glm::vec2, 4> texCoords = {};

		//const std::vector<SpriteSheet::Sprite>& currentAnimation = GetCurrentAnimation();
		const SpriteSheet::Sprite& currentSprite = GetCurrentSpriteInAnimation();

		const GT::Vector2<uint32_t>& spriteIndex = currentSprite.TextureCoordsIndex;
		const GT::Vector2<float> spriteSheetRatio = { spriteSheet.m_SpriteSize.x / spriteSheet.m_SpriteSheetSize.x, spriteSheet.m_SpriteSize.y / spriteSheet.m_SpriteSheetSize.y };

		texCoords[0] = { spriteIndex.x * spriteSheetRatio.x,         spriteIndex.y * spriteSheetRatio.y };
		texCoords[1] = { (spriteIndex.x + 1) * spriteSheetRatio.x,   spriteIndex.y * spriteSheetRatio.y };
		texCoords[2] = { (spriteIndex.x + 1) * spriteSheetRatio.x,  (spriteIndex.y + 1) * spriteSheetRatio.y };
		texCoords[3] = { spriteIndex.x * spriteSheetRatio.x,       (spriteIndex.y + 1) * spriteSheetRatio.y };

		return texCoords;
	}

	const std::vector<SpriteSheet::Sprite>& SpriteSheetView::GetCurrentAnimation() const
	{
		const SpriteSheet& spriteSheet = GetSpriteSheet();

		if (!m_CurrentAnimationHasChanged)
		{
			const auto animationIt = spriteSheet.m_Animations.find(m_CacheCurrentAnimationName);
			Assert(animationIt != spriteSheet.m_Animations.end(), "Animation with name {0} does not exist!", m_CacheCurrentAnimationName.c_str());
			return animationIt->second;
		}
		m_CurrentAnimationHasChanged = false;

		const auto currentAnimationIterator = spriteSheet.m_Animations.find(m_CurrentAnimationName);
		Assert(currentAnimationIterator != spriteSheet.m_Animations.end(), "Could not find animation {0}!", m_CurrentAnimationName.c_str());
		m_CacheCurrentAnimationName = currentAnimationIterator->first;

		return currentAnimationIterator->second;
	}
	const SpriteSheet::Sprite& SpriteSheetView::GetCurrentSpriteInAnimation() const
	{
		const std::vector<SpriteSheet::Sprite>& currentAnimation = GetCurrentAnimation();

		if (!m_CurrentSpriteHasChanged)
			return currentAnimation[m_CacheCurrentSpriteIndex];
		m_CurrentSpriteHasChanged = false;

		const SpriteSheet& spriteSheet = GetSpriteSheet();

		Assert(m_CurrentSpriteInAnimationIndex < spriteSheet.m_SpriteSheetSizeInTiles.x, "m_CurrentSpriteInAnimationIndex is out of bounds! :{0}", m_CurrentSpriteInAnimationIndex);
		m_CacheCurrentSpriteIndex = m_CurrentSpriteInAnimationIndex;

		return currentAnimation[m_CacheCurrentSpriteIndex];
	}

	// Private fuctions //

}