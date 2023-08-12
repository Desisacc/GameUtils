#pragma once

namespace GT {

	class ObjectInSystemComponent
	{
	public:
		static constexpr size_t INVALID_ID = std::numeric_limits<size_t>::max();
	public:
		ObjectInSystemComponent() = default;

		ObjectInSystemComponent(const ObjectInSystemComponent& other) noexcept
		{
			m_ObjectId = other.m_ObjectId;
		}
		ObjectInSystemComponent& operator=(const ObjectInSystemComponent& other) noexcept
		{
			if (this == &other)
				return *this;

			m_ObjectId = other.m_ObjectId;
			return *this;
		}
		ObjectInSystemComponent(ObjectInSystemComponent&& other) noexcept
		{
			m_ObjectId = other.m_ObjectId;
			other.m_ObjectId = INVALID_ID;
		}
		ObjectInSystemComponent& operator=(ObjectInSystemComponent&& other) noexcept
		{
			m_ObjectId = other.m_ObjectId;
			other.m_ObjectId = INVALID_ID;
			return *this;
		}

		void InitObjectId(size_t id)
		{
			m_ObjectId = id;
		}
		size_t GetObjectId() const
		{
			return m_ObjectId;
		}
		operator size_t() const
		{
			return GetObjectId();
		}
	private:
		size_t m_ObjectId = INVALID_ID;
	};

	template<typename T>
	class ObjectInSystem
	{
	public:
		ObjectInSystem() = default;
		ObjectInSystem(size_t id) noexcept
			: m_ObjectId(id) {}
		void Init(size_t id)
		{
			m_ObjectId = id;
		}

		size_t GetObjectId() const
		{
			return m_ObjectId;
		}
		operator size_t() const
		{
			return GetObjectId();
		}
	private:
		size_t m_ObjectId = ObjectInSystemComponent::INVALID_ID;
	};

}