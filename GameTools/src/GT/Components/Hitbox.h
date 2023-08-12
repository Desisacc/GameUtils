#pragma once

#include "GT/Components/Positional.h"

namespace GT {

	class Serializer;
	class Deserializer;

	namespace Component {

		struct Hitbox
		{
		private:
			// Position of the rectangle acts as an offset to the coordinates of the positional
			Rectangle m_HitboxRectangle;
		public:
			Hitbox() = default;
			Hitbox(Vector2<float> position, Vector2<float> size) noexcept
				: m_HitboxRectangle({ position, size }) {}
			void SetHitboxRectangle(Vector2<float> position, Vector2<float> size)
			{
				m_HitboxRectangle.Init(position, size);
			}

			void SetHitbox(Vector2<float> position)
			{
				SetHitboxHorizontally(position.x);
				SetHitboxVertically(position.y);
			}
			void SetHitboxHorizontally(float position)
			{
				m_HitboxRectangle.Position.x = position + m_HitboxRectangle.Position.x;
			}
			void SetHitboxVertically(float position)
			{
				m_HitboxRectangle.Position.y = position + m_HitboxRectangle.Position.y;
			}
			void MoveHitbox(Vector2<float> speed)
			{
				MoveHitboxHorizontally(speed.x);
				MoveHitboxVertically(speed.y);
			}
			void MoveHitboxHorizontally(float speed)
			{
				m_HitboxRectangle.MoveHorizontally(speed);
			}
			void MoveHitboxVertically(float speed)
			{
				m_HitboxRectangle.MoveVertically(speed);
			}

			const Rectangle& GetHitboxRectangle() const 
			{ 
				return m_HitboxRectangle; 
			}
			Vector2<float> GetHitboxPosition() const 
			{ 
				return m_HitboxRectangle.Position; 
			}
			Vector2<float> GetHitboxSize() const 
			{ 
				return m_HitboxRectangle.Size; 
			}

			/*Hitbox& GetHitbox() { return *this; }
			const Hitbox& GetHitBox() const { return *this; }*/

			friend class Serializer;
			friend class Deserializer;
		};

	}

}