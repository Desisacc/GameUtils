#include "gtpch.h"
#include "GT/Textures/SpriteSheet.h"

#include "GT/Components/Components.h"

namespace GT {

	void SpriteSheet::Init(const std::string& filepath, Vector2<float> spriteSize)
	{
		Init(Hazel::Texture2D::Create(filepath), spriteSize);
	}
	void SpriteSheet::Init(const Hazel::Ref<Hazel::Texture2D>& texture, Vector2<float> spriteSize)
	{
		m_Texture = texture;
		m_SpriteSheetSize = { (float)texture->GetWidth(), (float)texture->GetHeight() };
		
		// If the the given sprite size is zero, it will default to the size of the entire spritesheet 
		m_SpriteSize = spriteSize.x && spriteSize.y ? spriteSize : m_SpriteSheetSize;

		m_SpriteSheetSizeInTiles = { texture->GetWidth() / (uint32_t)m_SpriteSize.x, texture->GetHeight() / (uint32_t)m_SpriteSize.y };
	}
	void SpriteSheet::Init(const InitializerForSpriteSheet& spriteSheetData)
	{
		Init(spriteSheetData.Filepath, spriteSheetData.SpriteSize);

		for (auto& animationInfo : spriteSheetData.AnimationsInfo)
			AddAnimation(animationInfo.AnimationName, animationInfo.IndexForAnimation, animationInfo.NumberOfSpritesInAnimation);
	}

	SpriteSheet::SpriteSheet(const SpriteSheet& other) noexcept
	{
		ElementId::CopyIds(GetElementId(), other.GetElementId());

		m_Texture = other.m_Texture;
		m_SpriteSize = other.m_SpriteSize;
		m_SpriteSheetSize = other.m_SpriteSheetSize;
		m_SpriteSheetSizeInTiles = other.m_SpriteSheetSizeInTiles;

		m_Animations = other.m_Animations;
	}
	SpriteSheet& SpriteSheet::operator=(const SpriteSheet& other) noexcept
	{
		if (this != &other)
		{
			ElementId::CopyIds(GetElementId(), other.GetElementId());

			m_Texture = other.m_Texture;
			m_SpriteSize = other.m_SpriteSize;
			m_SpriteSheetSize = other.m_SpriteSheetSize;
			m_SpriteSheetSizeInTiles = other.m_SpriteSheetSizeInTiles;

			m_Animations = other.m_Animations;
		}		

		return *this;
	}

	SpriteSheet::SpriteSheet(SpriteSheet&& other) noexcept
	{
		ElementId::MoveIds(GetElementId(), other.GetElementId());

		m_Texture = other.m_Texture;
		other.m_Texture = nullptr;

		m_SpriteSize = other.m_SpriteSize;
		other.m_SpriteSize = { 0.0f, 0.0f };

		m_SpriteSheetSize = other.m_SpriteSheetSize;
		other.m_SpriteSheetSize = { 0.0f, 0.0f };

		m_SpriteSheetSizeInTiles = other.m_SpriteSheetSizeInTiles;
		other.m_SpriteSheetSizeInTiles = { 0, 0 };

		m_Animations = std::move(other.m_Animations);
		other.m_Animations.clear();
	}
	SpriteSheet& SpriteSheet::operator=(SpriteSheet&& other) noexcept
	{
		ElementId::MoveIds(GetElementId(), other.GetElementId());

		m_Texture = other.m_Texture;
		other.m_Texture = nullptr;

		m_SpriteSize = other.m_SpriteSize;
		other.m_SpriteSize = { 0.0f, 0.0f };

		m_SpriteSheetSize = other.m_SpriteSheetSize;
		other.m_SpriteSheetSize = { 0.0f, 0.0f };

		m_SpriteSheetSizeInTiles = other.m_SpriteSheetSizeInTiles;
		other.m_SpriteSheetSizeInTiles = { 0, 0 };

		m_Animations = std::move(other.m_Animations);
		other.m_Animations.clear();

		return *this;
	}

	void SpriteSheet::OnRender(const Component::Positional& positional, const std::array<glm::vec2, 4>& texCoords)
	{
		Assert(!m_Animations.empty(), "No animations were added to render!");

		const GT::Vector3<float> coords = positional.GetCoordinatesWithDepth();
		const GT::Vector2<float> size = positional.GetSize();

		Hazel::Renderer2D::DrawQuad({ coords.x, coords.y, coords.z }, { size.x, size.y }, m_Texture, texCoords);
	}

	void SpriteSheet::OnRender(const Component::Positional& positional, const Component::Rotational& rotational, const std::array<glm::vec2, 4>& texCoords)
	{		
		const Hazel::Renderer2D::QuadCenter currentQuadCenter = Hazel::Renderer2D::GetQuadCenter();
		const Vector2<float> centerCoordinates = positional.GetCoordinatesOfCenter();
		const GT::Vector2<float>& size = positional.GetRectangle().Size;

		Hazel::Renderer2D::SetQuadCenter(Hazel::Renderer2D::QuadCenter::Center);
		Hazel::Renderer2D::DrawRotatedQuad({ centerCoordinates.x, centerCoordinates.y, positional.GetDepth() }, { size.x, size.y }, rotational.GetDegrees(), m_Texture, texCoords);
		Hazel::Renderer2D::SetQuadCenter(currentQuadCenter);
	}

	void SpriteSheet::AddAnimation(const std::string& name, uint32_t indexOfAnimationInSpriteSheet, uint32_t numberOfSpritesInAnimation)
	{
		// Set number of sprites in animations
		if (!numberOfSpritesInAnimation)
			numberOfSpritesInAnimation = m_SpriteSheetSizeInTiles.x;
		
		// Set the sprites coordinates
		std::vector<Sprite> spritesInAnimation;
		for (uint32_t i = 0; i < numberOfSpritesInAnimation; i++)
			spritesInAnimation.emplace_back(i, indexOfAnimationInSpriteSheet);

		// Add animation to map
		m_Animations.insert({ name, spritesInAnimation });
	}

}