#include "TestLayer/TestApp.h"

namespace TestLayer {

	void TestApp::InitOverlays()
	{
		// Title Screen Overlay
		{
			GT::Overlay& titleScreen = AddOverlay("Title Screen");
			titleScreen.Init("assets/textures/BackgroundCastle.png", { 0.0f, 0.0f, 0.0f, 0.0f });

			// Start Button
			{
				GT::OverlayButton& startButton = titleScreen.AddButton();

				GT::SpriteSheet startButtonSpriteSheet;
				startButtonSpriteSheet.Init("assets/textures/StartButton.png", { 40.0f, 20.0f }, 0.0f);
				startButtonSpriteSheet.AddAnimation("Default", 0);

				startButton.Init({ 100.0f, 100.0f }, { 200.0f, 100.0f }, std::move(startButtonSpriteSheet), [this]() 
				{
					this->SetCurrentOverlay("Level Screen");
				});
			}

			// Close App Button
			{
				GT::OverlayButton& closeButton = titleScreen.AddButton();

				GT::SpriteSheet closeButtonSpriteSheet;
				closeButtonSpriteSheet.Init("assets/textures/EndButton.png", { 40.0f, 20.0f }, 0.0f);
				closeButtonSpriteSheet.AddAnimation("Default", 0);

				closeButton.Init({ 100.0f, 200.0f }, { 200.0f, 100.0f }, std::move(closeButtonSpriteSheet), []()
				{
					Hazel::Application::Get().Close();
				});
			}
		}

		// Pause Screen Overlay
		{
			GT::Overlay& pauseScreen = AddOverlay("Pause Screen");
			pauseScreen.Init({ 0.0f, 1.0f, 0.2f, 1.0f });

			// Quit Pause Screen Button
			{
				GT::OverlayButton& quitPauseButton = pauseScreen.AddButton();

				GT::SpriteSheet quitPauseButtonSpriteSheet;
				quitPauseButtonSpriteSheet.Init("assets/textures/StartButton.png", { 40.0f, 20.0f }, 0.0f);
				quitPauseButtonSpriteSheet.AddAnimation("Default", 0);

				quitPauseButton.Init({ 100.0f, 100.0f }, { 200.0f, 100.0f }, std::move(quitPauseButtonSpriteSheet), [this]()
				{
					this->QuitCurrentOverlay();
				});
			}

			// Close App Button
			{
				GT::OverlayButton& closeButton = pauseScreen.AddButton();

				GT::SpriteSheet closeButtonSpriteSheet;
				closeButtonSpriteSheet.Init("assets/textures/EndButton.png", { 40.0f, 20.0f }, 0.0f);
				closeButtonSpriteSheet.AddAnimation("Default", 0);

				closeButton.Init({ 100.0f, 200.0f }, { 200.0f, 100.0f }, std::move(closeButtonSpriteSheet), []()
				{
					Hazel::Application::Get().Close();
				});
			}
		}

		// Level Screen Overlay
		{
			GT::Overlay& levelScreen = AddOverlay("Level Screen");
			levelScreen.Init({ 0.8f, 0.1f, 0.2f, 1.0f });

			// Level One Button
			{
				GT::OverlayButton& levelOneButton = levelScreen.AddButton();

				GT::SpriteSheet levelOneButtonSpriteSheet;
				levelOneButtonSpriteSheet.Init("assets/textures/OneButton.png", { 40.0f, 20.0f }, 0.0f);
				levelOneButtonSpriteSheet.AddAnimation("Default", 0);

				levelOneButton.Init({ 0.0f, 0.0f }, { 200.0f, 100.0f }, std::move(levelOneButtonSpriteSheet), [this]()
				{
					LevelLoader::LoadLevelFromFile(1);
					this->QuitCurrentOverlay();
				});
			}
		}
	}

	void TestApp::Init()
	{
		InitOverlays();

		GlobalObjects::Init(m_Platforms, m_MovablePlatforms, m_JumpOrbs, m_Projectiles, m_Spikes, m_Player, m_EndFlag);
		LevelLoader::InitLevels();
		Platform::InitPlatforms();
		MovablePlatform::InitMovablePlatforms();
		JumpOrb::InitJumpOrbs();
		Projectile::InitProjectiles();
		Spike::InitSpikes();
		Player::InitPlayer();
		EndFlag::InitEndFlag();

		SetCurrentOverlay("Title Screen");

		/*auto& blockInts = m_Blocks.Get<int>();
		auto& blockPositionals = m_Blocks.Get<GT::Component::Positional>();
		for (int i = 0; i < 2; i++)
		{
			auto& block = blockPositionals.emplace_back();
			block.Init({ i * LevelSerializer::TILE_LENGTH, (float)GT::GlobalData::GetWindowHeight() - LevelSerializer::TILE_LENGTH }, LevelSerializer::TILE_SIZE);
		}
		auto& blockSprite = m_Blocks.GetSpriteSheet();
		blockSprite.Init("assets/textures/Projectile.png", { 20.0f, 20.0f }, 0.0f);
		blockSprite.AddAnimation("Default", 0);
		blockSprite.SetAnimation("Default");*/
	}

	void TestApp::OnUpdate(Hazel::Timestep ts)
	{
		// Updating the GameApp camera
		m_CameraOnUpdateArguments.ObjectToFollowPosition = m_Player.GetPositional().GetCoordinatesWithDepth();
		m_CameraOnUpdateArguments.ObjectToFollowSize = m_Player.GetPositional().GetRectangle().Size;

		// Updating game objects
		GlobalObjects::UpdateObjects(ts);

		// Load next level when player completes a level, go to title screen if all levels have been completed
		if (m_Player.HasCompletedLevel())
		{
			const bool hasCompletedGame = LevelLoader::LoadNextLevelFromFile();

			if (hasCompletedGame)
				SetCurrentOverlay("Title Screen");
		}

		// Pause screen when 'P' key is pressed
		if (Hazel::Input::IsKeyPressed(Hazel::Key::P))
			SetCurrentOverlay("Pause Screen");
	}

	void TestApp::OnRender()
	{
		// Render game objects
		GlobalObjects::RenderObjects();
	}

}