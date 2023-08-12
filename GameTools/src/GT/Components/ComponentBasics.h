#pragma once

#include <memory>

namespace GT {

	namespace Component	{

		template<typename ... types> struct HelperStruct {};

		template<typename T>
		struct IdInComponentSystem
		{
		public:
			IdInComponentSystem() = default;
			IdInComponentSystem(size_t id) noexcept
			{
				m_IdInVector = std::make_shared<size_t>(id);
			}

			operator size_t() const
			{
				return *m_IdInVector;
			}
			operator size_t& ()
			{
				return *m_IdInVector;
			}

			IdInComponentSystem<T>& operator=(size_t id)
			{
				if (!m_IdInVector)
					m_IdInVector = std::make_shared<size_t>();

				*m_IdInVector = id;
				return *this;
			}

			bool IsInitialized() const
			{
				return m_IdInVector.get() != nullptr;
			}
			void Invalidate()
			{
				m_IdInVector = nullptr;
			}
		private:
			std::shared_ptr<size_t> m_IdInVector = nullptr;
		};

	}

}