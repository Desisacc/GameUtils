#pragma once

#include "GT/Utils/Geometry.h"

namespace GT {

	class Serializer;
	class Deserializer;

	namespace Component {

		struct Positional
		{
		public:
			struct InitializerData
			{
				Vector2<float> Position = { 0.0f, 0.0f };
				Vector2<float> Size = { 0.0f, 0.0f };
				float Depth = 0.0f;
			};
		private:
			Rectangle m_Rectangle;
			float m_Depth = 0.0f;
		public:
			Positional() = default;
			Positional(const InitializerData& initializerData) noexcept
			{
				SetPositional(initializerData);
			}
			void SetPositional(const InitializerData& initializerData)
			{
				m_Rectangle.Init(initializerData.Position, initializerData.Size);
				SetDepth(initializerData.Depth);
			}

			void SetRectangle(Vector2<float> position, Vector2<float> size)
			{
				m_Rectangle.Init(position, size);
			}
			void SetSize(Vector2<float> size)
			{
				m_Rectangle.Size = size;
			}
			void SetDepth(float depth)
			{
				m_Depth = depth;
			}

			void SetPosition(Vector2<float> position) 
			{ 
				SetHorizontally(position.x);
				SetVertically(position.y);
			}
			void SetHorizontally(float position)
			{
				m_Rectangle.Position.x = position;
			}
			void SetVertically(float position)
			{
				m_Rectangle.Position.y = position;
			}
			void Move(Vector2<float> speed)
			{
				MoveHorizontally(speed.x);
				MoveVertically(speed.y);
			}
			void MoveHorizontally(float speed)
			{
				m_Rectangle.MoveHorizontally(speed);
			}
			void MoveVertically(float speed)
			{
				m_Rectangle.MoveVertically(speed);
			}

			Vector3<float> GetCoordinatesWithDepth() const
			{
				return { m_Rectangle.Position.x, m_Rectangle.Position.y, m_Depth };
			}
			Vector2<float> GetCoordinatesOfCenter() const
			{
				return { m_Rectangle.Position.x + m_Rectangle.Size.x / 2.0f, m_Rectangle.Position.y + m_Rectangle.Size.y / 2.0f };
			}
			Vector3<float> GetCoordinatesOfCenterWithDepth() const
			{
				const Vector2<float> centerPosition = GetCoordinatesOfCenter();
				return { centerPosition.x, centerPosition.y, m_Depth };
			}

			const Rectangle& GetRectangle() const { return m_Rectangle; }
			Vector2<float> GetPosition() const { return m_Rectangle.Position; }
			Vector2<float> GetSize() const { return m_Rectangle.Size; }
			float GetDepth() const { return m_Depth; }

			/*Positional& GetPositional() { return *this; }
			const Positional& GetPositional() const { return *this; }*/

			friend class Serializer;
			friend class Deserializer;
		};

	}

}