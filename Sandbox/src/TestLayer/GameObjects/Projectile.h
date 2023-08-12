#pragma once

#include <GT.h>

namespace TestLayer {

	class Player;

	class Projectile : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Projectile>, GT::Component::Directional, GT::Component::Rotational>
	{
	public:
		static constexpr float PROJECTILE_SPEED = 200.0f;
		static constexpr float PROJECTILE_LENGTH = 20.0f;
		static const GT::Vector2<float> PROJECTILE_SIZE;
	public:
		Projectile() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, GT::Vector2<float> speed, float depth = 0.0f);
		static void InitProjectiles();

		void OnUpdate(Hazel::Timestep ts);
	private:
		void UpdateMovement(Hazel::Timestep ts);
	};

	/*
	struct OnUpdateArguments
	{
		const Player& PlayerToFollow;

		OnUpdateArguments(const Player& playerToFollow) noexcept
			: PlayerToFollow(playerToFollow) {}
	};
	static std::shared_ptr<OnUpdateArguments> s_OnUpdateArguments;
	std::shared_ptr<Projectile::OnUpdateArguments> Projectile::s_OnUpdateArguments = nullptr;
	s_OnUpdateArguments = std::make_shared<OnUpdateArguments>(playerToFollow);
	const Player& player = s_OnUpdateArguments->PlayerToFollow;
	*/

}