#pragma once

#include "TestLayer/GameObjects/Player.h"
#include "TestLayer/GameObjects/Platform.h"
#include "TestLayer/GameObjects/MovablePlatform.h"
#include "TestLayer/GameObjects/JumpOrb.h"
#include "TestLayer/GameObjects/Projectile.h"
#include "TestLayer/GameObjects/Spike.h"
#include "TestLayer/GameObjects/EndFlag.h"
#include "TestLayer/LevelLoader.h"

namespace TestLayer {

	class GlobalObjects
	{
	public:
		GlobalObjects() = delete;
		static void Init(std::vector<Platform>& platforms, std::vector<MovablePlatform>& movablePlatforms, std::vector<JumpOrb>& jumpOrbs,
			std::vector<Projectile>& projectiles, std::vector<Spike>& spikes, Player& player, EndFlag& endFlag);

		static void UpdateObjects(Hazel::Timestep ts);
		static void RenderObjects();

		static void ClearObjectsOfLevel(LevelLoader::Level& level);
		static void LoadObjectsFromLevel(const LevelLoader::Level& level);

		static std::vector<Platform>& GetPlatforms() { return *m_PlatformsRef; }
		static std::vector<MovablePlatform>& GetMovablePlatforms() { return *m_MovablePlatformsRef; }
		static std::vector<JumpOrb>& GetJumpOrbs() { return *m_JumpOrbsRef; }
		static std::vector<Projectile>& GetProjectiles() { return *m_ProjectilesRef; }
		static std::vector<Spike>& GetSpikes() { return *m_SpikesRef; }
		static Player& GetPlayer() { return *m_PlayerRef; }
		static EndFlag& GetEndFlag() { return *m_EndFlagRef; }
	private:
		static std::vector<Platform>* m_PlatformsRef;
		static std::vector<MovablePlatform>* m_MovablePlatformsRef;
		static std::vector<JumpOrb>* m_JumpOrbsRef;
		static std::vector<Projectile>* m_ProjectilesRef;
		static std::vector<Spike>* m_SpikesRef;
		static Player* m_PlayerRef;
		static EndFlag* m_EndFlagRef;
	};

}