#pragma once

#include "GT/Components/Positional.h"

namespace GT {

	class Serializer;
	class Deserializer;

	namespace Component {

		struct Rotational
		{
		private:
			float m_Degrees = 0.0f;
		public:
			Rotational(float degrees) noexcept
				: m_Degrees(degrees) {}
			Rotational() = default;
			void SetRotational(float degrees)
			{
				m_Degrees = degrees;
			}

			float GetDegrees() const
			{
				return m_Degrees;
			}
			void SetDegrees(float degrees)
			{
				m_Degrees = degrees;
			}

			/*Rotational& GetRotational() { return *this; }
			const Rotational& GetRotational() const { return *this; }*/

			friend class Serializer;
			friend class Deserializer;
		};

	}

}