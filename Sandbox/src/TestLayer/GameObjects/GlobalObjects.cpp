#include "TestLayer/GameObjects/GlobalObjects.h"

namespace TestLayer {

	std::vector<Platform>* GlobalObjects::m_PlatformsRef = nullptr;
	std::vector<MovablePlatform>* GlobalObjects::m_MovablePlatformsRef = nullptr;
	std::vector<JumpOrb>* GlobalObjects::m_JumpOrbsRef = nullptr;
	std::vector<Projectile>* GlobalObjects::m_ProjectilesRef = nullptr;
	std::vector<Spike>* GlobalObjects::m_SpikesRef;
	Player* GlobalObjects::m_PlayerRef = nullptr;
	EndFlag* GlobalObjects::m_EndFlagRef = nullptr;

	void GlobalObjects::Init(std::vector<Platform>& platforms, std::vector<MovablePlatform>& movablePlatforms, std::vector<JumpOrb>& jumpOrbs, 
		std::vector<Projectile>& projectiles, std::vector<Spike>& spikes, Player& player, EndFlag& endFlag)
	{
		m_PlatformsRef = &platforms;
		m_MovablePlatformsRef = &movablePlatforms;
		m_JumpOrbsRef = &jumpOrbs;
		m_ProjectilesRef = &projectiles;
		m_SpikesRef = &spikes;
		m_PlayerRef = &player;
		m_EndFlagRef = &endFlag;
	}

	void GlobalObjects::UpdateObjects(Hazel::Timestep ts)
	{
		for (MovablePlatform& movablePlatform : GetMovablePlatforms())
			movablePlatform.OnUpdate(ts);

		for (Spike& spike : GetSpikes())
			spike.OnUpdate(ts);

		for (Projectile& projectile : GetProjectiles())
			projectile.OnUpdate(ts);

		GetPlayer().OnUpdate(ts);
	}

	void GlobalObjects::RenderObjects()
	{
		for (Projectile& projectile : GetProjectiles())
			projectile.OnRender();

		for (MovablePlatform& movablePlatform : GetMovablePlatforms())
			movablePlatform.OnRender();

		for (Platform& platform : GetPlatforms())
			platform.OnRender();

		for (JumpOrb& jumpOrb : GetJumpOrbs())
			jumpOrb.OnRender();

		for (Spike& spike : GetSpikes())
			spike.OnRender();

		GetEndFlag().OnRender();

		GetPlayer().OnRender();
	}

	void GlobalObjects::ClearObjectsOfLevel(LevelLoader::Level& level)
	{
		level.Platforms.clear();
		level.MovablePlatforms.clear();
		level.Spikes.clear();
		level.Projectiles.clear();
		level.JumpOrbs.clear();
	}

	void GlobalObjects::LoadObjectsFromLevel(const LevelLoader::Level& level)
	{
		GetPlayer() = level.Player;
		GetEndFlag() = level.EndFlag;
		GetPlatforms() = level.Platforms;
		GetMovablePlatforms() = level.MovablePlatforms;
		GetSpikes() = level.Spikes;
		GetProjectiles() = level.Projectiles;
		GetJumpOrbs() = level.JumpOrbs;
	}

}