#pragma once

#include "GT/Components/Positional.h"
#include "GT/Textures/SpriteSheet.h"
#include "GT/Textures/SpriteSheetView.h"

namespace GT {

	class Serializer;
	class Deserializer;

	namespace Component {

		/*class Renderable
		{
		public:
			Renderable() = default;
			virtual ~Renderable() = default;

			virtual void InitRenderable(const SpriteSheet::InitializerForSpriteSheet& initializerData) = 0;

			virtual void SetAnimation(const std::string& name, uint32_t indexOfStartingSprite = 0) = 0;

			virtual void OnUpdate(Hazel::Timestep ts) = 0;
			virtual void OnRender(Positional& positional) = 0;
		};

		template<typename NameOfTheClass>
		struct ClassRenderable : public Renderable
		{
		protected:
			static SpriteSheet s_SpriteSheetOfClass;
			SpriteSheetView m_SpriteSheetViewOfObject;
		public:
			virtual void InitRenderable(const SpriteSheet::InitializerForSpriteSheet& initializerData) override
			{
				auto& spriteSheet = s_SpriteSheetOfClass;
				auto& spriteSheetView = m_SpriteSheetViewOfObject;

				// Giving filepath, spriteSize to the spriteSheet and adding all animations
				spriteSheet.Init(initializerData.Filepath, initializerData.SpriteSize);
				for (const auto& animationPairInfo : initializerData.AnimationsInfo)
					spriteSheet.AddAnimation(animationPairInfo.AnimationName, animationPairInfo.IndexForAnimation, animationPairInfo.NumberOfSpritesInAnimation);

				// Giving the corresponding spriteSheet address to the spriteSheetView and setting its timer, 
				// also setting by default the first animation in the list if it's not empty
				spriteSheetView.Init(&spriteSheet, initializerData.TimerForSprites);
				if (!initializerData.AnimationsInfo.empty())
					spriteSheetView.SetAnimation(initializerData.AnimationsInfo.front().AnimationName);
			}

			virtual void SetAnimation(const std::string& name, uint32_t indexOfStartingSprite = 0) override
			{
				m_SpriteSheetViewOfObject.SetAnimation(name, indexOfStartingSprite);
			}

			virtual void OnUpdate(Hazel::Timestep ts) override
			{
				m_SpriteSheetViewOfObject.OnUpdate(ts);
			}
			virtual void OnRender(Positional& positional) override
			{
				m_SpriteSheetViewOfObject.OnRender(positional);
			}

			//TEMP
			//static SpriteSheet& GetSpriteSheetOfClass() { return s_SpriteSheetOfClass; }
			//SpriteSheetView& GetSpriteSheetView() { return m_SpriteSheetViewOfObject; }
		};
		template<typename NameOfTheClass> SpriteSheet ClassRenderable<NameOfTheClass>::s_SpriteSheetOfClass = SpriteSheet();*/

		struct ObjectRenderable
		{
		public:
			struct InitializerData
			{
				size_t SpriteSheetId = std::numeric_limits<size_t>::max();
				// If left as zero the update function won't do anything
				float TimerForSprites = 0.0f;
				std::string DefaultAnimationName;
				// Leave at zero if it default animation has the same number of sprites than the lenght of the spriteSheet
				uint32_t NumberOfSpritesInDefaultAnimation = 0;
			};
		protected:
			SpriteSheetView m_SpriteSheetView;
		public:
			void InitRenderable(const InitializerData& spriteSheetViewData)
			{
				m_SpriteSheetView.Init(spriteSheetViewData.SpriteSheetId, spriteSheetViewData.TimerForSprites);
				m_SpriteSheetView.SetAnimation(spriteSheetViewData.DefaultAnimationName, spriteSheetViewData.NumberOfSpritesInDefaultAnimation);
				/*auto& spriteSheet = m_SpriteSheetRenderableOfObject.SpriteSheetOfObject;
				auto& spriteSheetView = m_SpriteSheetRenderableOfObject.SpriteSheetViewOfObject;

				// Giving filepath, spriteSize to the spriteSheet and adding all animations
				spriteSheet.Init(initializerData.Filepath, initializerData.SpriteSize);
				for (const auto& animationPairInfo : initializerData.AnimationsInfo)
					spriteSheet.AddAnimation(animationPairInfo.AnimationName, animationPairInfo.IndexForAnimation, animationPairInfo.NumberOfSpritesInAnimation);
				
				// Giving the corresponding spriteSheet address to the spriteSheetView and setting its timer, 
				// also setting by default the first animation in the list if it's not empty
				spriteSheetView.Init(&spriteSheet, initializerData.TimerForSprites);
				if (!initializerData.AnimationsInfo.empty())
					spriteSheetView.SetAnimation(initializerData.AnimationsInfo.front().AnimationName);*/
			}
			
			void SetAnimation(const std::string& name, uint32_t indexOfStartingSprite = 0)
			{
				m_SpriteSheetView.SetAnimation(name, indexOfStartingSprite);
			}

			size_t GetSpriteSheetId() const
			{
				return m_SpriteSheetView.GetSpriteSheetId();
			}

			void SetIsRendered(bool isRendered)
			{
				m_SpriteSheetView.SetIsRendered(isRendered);
			}
			bool IsRendered() const
			{
				return m_SpriteSheetView.GetIsRendered();
			}

			void OnUpdate(Hazel::Timestep ts)
			{
				m_SpriteSheetView.OnUpdate(ts);
			}
			void OnRender(Positional& positional)
			{
				m_SpriteSheetView.OnRender(positional);
			}

			//TEMP
			//SpriteSheet& GetSpriteSheetOfObject() { return SpriteSheetRenderableOfObject.SpriteSheetOfObject; }
			//SpriteSheetView& GetSpriteSheetView() { return SpriteSheetRenderableOfObject.SpriteSheetViewOfObject; }
		};

		/*template<typename NameOfTheClass>
		struct ClassRenderable : virtual public Positional
		{
		protected:
			static SpriteSheet SpriteSheetOfClass;
			SpriteSheetView SpriteSheetViewOfObject;
		public:
			static void OnUpdate(Hazel::Timestep ts, ClassRenderable<NameOfTheClass>& component)
			{
				component.SpriteSheetViewOfObject.OnUpdate(ts);
			}

			void OnRender()
			{
				SpriteSheetViewOfObject.OnRender(GetPositional());
			}

			//TEMP
			static SpriteSheet& GetSpriteSheetOfClass() { return SpriteSheetOfClass; }
			SpriteSheetView& GetSpriteSheetView() { return SpriteSheetViewOfObject; }
		};
		template<typename NameOfTheClass> SpriteSheet ClassRenderable<NameOfTheClass>::SpriteSheetOfClass = SpriteSheet();

		struct Renderable : virtual public Positional
		{
		protected:
			SpriteSheetRenderable m_RenderableObject;
		public:
			static void OnUpdate(Hazel::Timestep ts, Renderable& component)
			{
				component.m_RenderableObject.SpriteSheetViewOfObject.OnUpdate(ts);
			}

			void OnRender()
			{
				m_RenderableObject.SpriteSheetViewOfObject.OnRender(GetPositional());
			}

			//TEMP
			SpriteSheet& GetSpriteSheetOfObject() { return m_RenderableObject.SpriteSheetOfObject; }
			SpriteSheetView& GetSpriteSheetView() { return m_RenderableObject.SpriteSheetViewOfObject; }
		};*/
	}

}