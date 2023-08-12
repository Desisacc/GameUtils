#include "MouseGame/MouseGameObjects/Interactable.h"

#include "MouseGame/MouseGameObjects/GlobalMouseGameObjects.h"

namespace MouseGameLayer {

	void Interactable::InitInteractables()
	{
		// Button One
		{
			GT::SpriteSheet::InitializerForSpriteSheet buttonOneSpriteSheetData;
			buttonOneSpriteSheetData.Filepath = "assets/textures/ButtonOne.png";
			buttonOneSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::ButtonOne_SSI, buttonOneSpriteSheetData);

			GT::Component::ObjectRenderable::InitializerData buttonOneViewData;
			buttonOneViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::ButtonOne_SSI;
			buttonOneViewData.DefaultAnimationName = "Default";

			GT::Component::Positional::InitializerData buttonOnePositionalData;
			buttonOnePositionalData.Position = { 100.0f, 100.0f };
			buttonOnePositionalData.Size = { 50.0f, 50.0f };

			GT::LoadingSystem<Interactable>::AddObjectToMap(InteractableIds::ButtonOne, buttonOneViewData, buttonOnePositionalData);
			GT::LoadingSystem<Interactable>::LoadObjectNoRender(InteractableIds::ButtonOne, [](Interactable& buttonOne) 
				{
					buttonOne.SetAction([]() 
						{ 
							GlobalMouseGameObjects::ButtonOneHasBeenPressed = true; 
							GT::Component::Positional::InitializerData& masterKeyPositionalData = GT::LoadingSystem<Item>::GetUnloadedObject(Item::ItemIds::MasterKey_II).PositionalData;
							masterKeyPositionalData.Size = { 50.0f, 50.0f };
						});
				});
		}
	}

	void Interactable::Init(const GT::Component::Positional::InitializerData& positionalData, GT::Component::ObjectRenderable::InitializerData& spriteSheetData, std::function<void()> onAction)
	{
		Get<GT::Component::Positional>().SetPositional(positionalData);
		Get<GT::Component::ObjectRenderable>().InitRenderable(spriteSheetData);
		m_OnAction = onAction;
	}

	void Interactable::OnUpdate(Hazel::Timestep ts)
	{
		auto& clickableObject = Get<ClickableObject>();

		clickableObject.OnUpdateClickableObject(Get<GT::Component::Positional>());

		if (clickableObject.IsBeingClicked())
			m_OnAction();

		Get<GT::Component::ObjectRenderable>().OnUpdate(ts);
	}

	void Interactable::OnRender()
	{
		Get<GT::Component::ObjectRenderable>().OnRender(Get<GT::Component::Positional>());
	}

}