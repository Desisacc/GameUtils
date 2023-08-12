#pragma once

#include <array>

#include "GT/Utils/Assert.h"

namespace GT {

	template<typename T>
	class Vector2
	{
	private:
		static constexpr uint32_t VECTOR_COUNT = 2;
		static constexpr size_t VECTOR_SIZE_IN_BYTES = sizeof(T) * VECTOR_COUNT;
	public:
		Vector2() = default;
		Vector2(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector2 was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
		}
		Vector2<T>& operator=(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector2 was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
			return *this;
		}

		Vector2(const Vector2<T>& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector2<T>& operator=(const Vector2<T>& other) noexcept
		{
			if (this != &other)
			{
				memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			}
			return *this;
		}

		// Move semantics are not allowed, will use copy constructor
		Vector2(Vector2<T>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector2<T>& operator=(Vector2<T>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			return *this;
		}

		T& operator[](size_t index) { return m_Data[index]; }
		const T& operator[](size_t index) const { return m_Data[index]; }

		bool operator==(const Vector2<T>& other) const
		{
			return x == other.x && y == other.y;
		}
	public:
		T& x = m_Data[0];
		T& y = m_Data[1];
	private:
		std::array<T, VECTOR_COUNT> m_Data;
	};

	template<typename T>
	class Vector3
	{
	private:
		static constexpr uint32_t VECTOR_COUNT = 3;
		static constexpr size_t VECTOR_SIZE_IN_BYTES = sizeof(T) * VECTOR_COUNT;
	public:
		Vector3() = default;
		Vector3(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector3 was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
		}
		Vector3<T>& operator=(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector3 was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
			return *this;
		}

		Vector3(const Vector3<T>& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector3<T>& operator=(const Vector3<T>& other) noexcept
		{
			if (this != &other)
			{
				memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			}
			return *this;
		}

		// Move semantics are not allowed, will use copy constructor
		Vector3(Vector3<T>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector3<T>& operator=(Vector3<T>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			return *this;
		}

		T& operator[](size_t index) { return m_Data[index]; }
		const T& operator[](size_t index) const { return m_Data[index]; }

		bool operator==(const Vector3<T>& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}
	public:
		T& x = m_Data[0];
		T& y = m_Data[1];
		T& z = m_Data[2];
	private:
		std::array<T, VECTOR_COUNT> m_Data;
	};

	template<typename T>
	class Vector4
	{
	private:
		static constexpr uint32_t VECTOR_COUNT = 4;
		static constexpr size_t VECTOR_SIZE_IN_BYTES = sizeof(T) * VECTOR_COUNT;
	public:
		Vector4() = default;
		Vector4(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector4 was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
		}
		Vector4<T>& operator=(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector4 was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
			return *this;
		}

		Vector4(const Vector4<T>& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector4<T>& operator=(const Vector4<T>& other) noexcept
		{
			if (this != &other)
			{
				memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			}
			return *this;
		}

		// Move semantics are not allowed, will use copy constructor
		Vector4(Vector4<T>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector4<T>& operator=(Vector4<T>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			return *this;
		}

		T& operator[](size_t index) { return m_Data[index]; }
		const T& operator[](size_t index) const { return m_Data[index]; }

		bool operator==(const Vector4<T>& other) const
		{
			return r == other.r && g == other.g && b == other.b && a == other.a;
		}
	public:
		T& r = m_Data[0];
		T& g = m_Data[1];
		T& b = m_Data[2];
		T& a = m_Data[3];
	private:
		std::array<T, VECTOR_COUNT> m_Data;
	};

	/*template<typename T, size_t VECTOR_COUNT>
	class Vector
	{
	private:
		static constexpr size_t VECTOR_SIZE_IN_BYTES = sizeof(T) * VECTOR_COUNT;
	public:
		Vector() = default;
		Vector(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
		}
		Vector<T, VECTOR_COUNT>& operator=(std::initializer_list<T> values) noexcept
		{
			Assert(values.size() == VECTOR_COUNT, "Vector was initialized with a list of values of size {0}", values.size());
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, values.begin(), values.size() * sizeof(T));
			return *this;
		}

		Vector(const Vector2<T, VECTOR_COUNT>& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector<T, VECTOR_COUNT>& operator=(const Vector<T, VECTOR_COUNT>& other) noexcept
		{
			if (this != &other)
			{
				memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			}
			return *this;
		}

		Vector(Vector<T, VECTOR_COUNT>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
		}
		Vector<T, VECTOR_COUNT>& operator=(Vector<T, VECTOR_COUNT>&& other) noexcept
		{
			memcpy_s(m_Data.data(), VECTOR_SIZE_IN_BYTES, other.m_Data.data(), VECTOR_SIZE_IN_BYTES);
			return *this;
		}

		T& operator[](size_t index) { return m_Data[index]; }
		const T& operator[](size_t index) const { return m_Data[index]; }
	private:
		std::array<T, VECTOR_COUNT> m_Data;
	};

	template<typename T>
	class Vector2
	{
	private:
		static constexpr uint32_t VECTOR_COUNT = 2;
		static constexpr size_t VECTOR_SIZE_IN_BYTES = sizeof(T) * VECTOR_COUNT;
	public:
		constexpr Vector2() = default;
		constexpr Vector2(std::initializer_list<T> values) noexcept
		{
			x = *(values.begin() + 0);
			y = *(values.begin() + 1);
		}
		constexpr Vector2<T>& operator=(std::initializer_list<T> values) noexcept
		{
			x = *(values.begin() + 0);
			y = *(values.begin() + 1);
			return *this;
		}

		constexpr Vector2(const Vector2<T>& other) noexcept
		{
			x = other.x;
			y = other.y;
		}
		constexpr Vector2<T>& operator=(const Vector2<T>& other) noexcept
		{
			if (this != &other)
			{
				x = other.x;
				y = other.y;
			}
			return *this;
		}

		constexpr Vector2(Vector2<T>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
		}
		constexpr Vector2<T>& operator=(Vector2<T>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			return *this;
		}
	public:
		T x = m_Data[0];
		T y = m_Data[1];
	};

	inline void myFunc()
	{
		constexpr glm::uvec2  glmvec = { 0, 1 };
		std::initializer_list;
		auto list = { 0, 1 };
		constexpr Vector2<int> myVec2(std::initializer_list<int>());
	}*/

}