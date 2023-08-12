#pragma once

#include <GT.h>

#include "TestLayer/GameObjects/GlobalObjects.h"
#include "TestLayer/GameObjects/Player.h"
#include "TestLayer/GameObjects/Platform.h"
#include "TestLayer/GameObjects/JumpOrb.h"
#include "TestLayer/GameObjects/Projectile.h"
#include "TestLayer/GameObjects/Spike.h"
#include "TestLayer/GameObjects/EndFlag.h"

#include "TestLayer/GameObjects/MovablePlatform.h"

#include "TestLayer/LevelLoader.h"
#include "TestLayer/LevelSerializer.h"

// TODO: Level editor
// TODO: Change LevelLoader::ResetCurrentLevel() so it doesn't have to serialize the entire level again
// TODO: Change LevelLoader::Serializer so that it optimizes smaller platforms into longer ones

namespace TestLayer {

	class TestApp : public GT::BaseGameApp
	{
	protected:
		virtual void Init() override;
		virtual void OnUpdate(Hazel::Timestep ts) override;
		virtual void OnRender() override;
	private:
		void InitOverlays();
	private:
		std::vector<Platform> m_Platforms;
		std::vector<MovablePlatform> m_MovablePlatforms;
		std::vector<JumpOrb> m_JumpOrbs;
		std::vector<Projectile> m_Projectiles;
		std::vector<Spike> m_Spikes;
		Player m_Player;
		EndFlag m_EndFlag;
	};

}