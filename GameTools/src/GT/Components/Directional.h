#pragma once

#include "GT/Components/Positional.h"

namespace GT {

	class Serializer;
	class Deserializer;

	namespace Component {

		struct Directional
		{
		private:
			Vector2<float> m_Speed = { 0.0f, 0.0f };
			Vector2<float> m_SpeedFromLastUpdate = { 0.0f, 0.0f };
			Rectangle m_PreviousRectangle;
		public:
			enum MovementDirection : uint32_t
			{
				None_MD = 0, Left_MD = 1, Right_MD = 2, Down_MD = 4, Up_MD = 8,

				LeftDown_MD = Left_MD | Down_MD,
				LeftUp_MD = Left_MD | Up_MD,
				RightDown_MD = Right_MD | Down_MD,
				RightUp_MD = Right_MD | Up_MD
			};

			Directional() = default;
			Directional(Vector2<float> speed) noexcept
				: m_Speed(speed) {}
			void SetDirectional(Vector2<float> speed)
			{
				m_Speed = speed;
			}

			void UpdatePreviousState(const Positional& positional)
			{
				m_SpeedFromLastUpdate = m_Speed;
				m_PreviousRectangle = positional.GetRectangle();
			}
			Vector2<float> GetTraveledDistance(const Positional& positional) const
			{
				return { positional.GetPosition().x - m_PreviousRectangle.Position.x, positional.GetPosition().y - m_PreviousRectangle.Position.y };
			}
			MovementDirection GetMovementDirectionFromLastUpdate() const
			{
				MovementDirection movementDirection = None_MD;

				if (m_SpeedFromLastUpdate.x > 0.0f)
					movementDirection = (MovementDirection)(movementDirection | Right_MD);
				else if (m_SpeedFromLastUpdate.x < 0.0f)
					movementDirection = (MovementDirection)(movementDirection | Left_MD);

				if (m_SpeedFromLastUpdate.y > 0.0f)
					movementDirection = (MovementDirection)(movementDirection | Up_MD);
				else if (m_SpeedFromLastUpdate.y < 0.0f)
					movementDirection = (MovementDirection)(movementDirection | Down_MD);

				return movementDirection;
			}

			void SetSpeed(Vector2<float> speed) 
			{ 
				SetSpeedHorizontally(speed.x);
				SetSpeedVertically(speed.y);
			}
			void SetSpeedHorizontally(float speed) 
			{ 
				m_Speed.x = speed; 
			}
			void SetSpeedVertically(float speed) 
			{ 
				m_Speed.y = speed; 
			}
			
			Vector2<float> GetSpeed() const 
			{ 
				return m_Speed; 
			}
			const Rectangle& GetPreviousRectangle() const 
			{ 
				return m_PreviousRectangle; 
			}
			Vector2<float> GetSpeedFromLastUpdate() const 
			{ 
				return m_SpeedFromLastUpdate; 
			}

			/*Directional& GetDirectional() { return *this; }
			const Directional& GetDirectional() const { return *this; }*/

			friend class Serializer;
			friend class Deserializer;
		};

	}

}