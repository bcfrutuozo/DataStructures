#pragma once

#include "IEquatable.h"
#include "IComparable.h"
#include "IConvertible.h"
#include "Primitives.h"

class Boolean;

class Int32 final: public Primitive<int>, public IComparable<Int32>, public IConvertible, public IEquatable<Int32>
{
private:

	constexpr Int32(Primitive<int> const& value) : Primitive(value.Get()) { }

public:

	constexpr Int32() noexcept : Primitive() {}
	constexpr Int32(const int& value) noexcept : Primitive(value) { }
	constexpr Int32(const Int32& value) noexcept : Primitive(value) { }

	Int32(Int32&&) = default;
	Int32& operator=(Int32 const&) = default;
	Int32& operator=(Int32&&) = default;

	template<typename U, typename = std::enable_if_t<is_conversion<U, int>::value>>
	constexpr static Int32 From(U const& other) noexcept { return Int32(U(other)); }

	constexpr Int32 const& operator+() const noexcept { return *this; }
	constexpr Int32 operator-() const noexcept { return Int32(-m_value); }
	constexpr Int32 operator~() const noexcept { return Int32(~m_value); }
	constexpr bool operator!() const noexcept { return !m_value; }

	constexpr Int32& operator++() noexcept
	{
		++m_value;
		return *this;
	}

	constexpr Int32 operator++(int) noexcept
	{
		return Int32(m_value++);
	}

	constexpr Int32& operator--() noexcept
	{
		--m_value;
		return *this;
	}

	constexpr Int32 operator--(int) noexcept
	{
		return Int32(m_value--);
	}

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	Int32& operator+=(U const& other) noexcept
	{
		m_value += other;
		return *this;
	}

	template<typename U>
	Int32& operator+=(Primitive<U> const& other) noexcept
	{
		m_value += other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	Int32& operator-=(U const& other) noexcept
	{
		m_value -= other;
		return *this;
	}

	template<typename U>
	Int32& operator-=(Primitive<U> const& other) noexcept
	{
		m_value -= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	Int32& operator*=(U const& other) noexcept
	{
		m_value *= other;
		return *this;
	}

	template<typename U>
	Int32& operator*=(Primitive<U> const& other) noexcept
	{
		m_value *= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	Int32& operator/=(U const& other) noexcept
	{
		m_value /= other;
		return *this;
	}

	template<typename U>
	Int32& operator/=(Primitive<U> const& other) noexcept
	{
		m_value /= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator%=(U const& other) noexcept
	{
		m_value %= other;
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator%=(Primitive<U> const& other) noexcept
	{
		m_value %= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator<<=(U const& other) noexcept
	{
		m_value <<= other;
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator<<=(Primitive<U> const& other) noexcept
	{
		m_value <<= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator>>=(U const& other) noexcept
	{
		m_value >>= other;
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator>>=(Primitive<U> const& other) noexcept
	{
		m_value >>= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator&=(U const& other) noexcept
	{
		m_value &= other;
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator&=(Primitive<U> const& other) noexcept
	{
		m_value &= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator|=(U const& other) noexcept
	{
		m_value |= other;
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator|=(Primitive<U> const& other) noexcept
	{
		m_value |= other.Get();
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator^=(U const& other) noexcept
	{
		m_value ^= other;
		return *this;
	}

	template<typename U, typename = std::enable_if_t< std::is_integral<int>::value&& std::is_integral<U>::value>>
	Int32& operator^=(Primitive<U> const& other) noexcept
	{
		m_value ^= other.Get();
		return *this;
	}

	friend std::istream& operator>>(std::istream& lhs, Int32& const rhs) { return lhs >> rhs.m_value; }
	friend std::ostream& operator<<(std::ostream& lhs, Int32& const rhs) { return lhs << rhs.m_value; }

	/*Int32 operator+(Boolean const& other) const noexcept;*/

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator+(U const& other) noexcept { return Int32(other + m_value); }

	template<typename U>
	constexpr Int32 operator+(Primitive<U> const& other) const noexcept { return Int32(other.Get() + m_value); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator-(U const& other) noexcept { return Int32(m_value - other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator*(U const& other) noexcept { return Int32(m_value * other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator/(U const& other) noexcept { return Int32(m_value / other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator%(U const& other) noexcept { return Int32(m_value % other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator&(U const& other) noexcept { return Int32(m_value & other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator|(U const& other) noexcept { return Int32(m_value | other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator^(U const& other) noexcept { return Int32(m_value ^ other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator<<(U const& other) noexcept { return Int32(m_value << other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr Int32 operator>>(U const& other) noexcept { return Int32(m_value >> other); }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr bool operator==(U const& other) noexcept { return m_value == other; }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr bool operator!=(U const& other) noexcept { return m_value != other; }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr bool operator<(U const& other) noexcept { return m_value < other; }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr bool operator<=(U const& other) noexcept { return m_value <= other; }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr bool operator>(U const& other) noexcept { return m_value > other; }

	template<typename U, typename = std::enable_if_t<std::is_fundamental<U>::value>>
	constexpr bool operator>=(U const& other) noexcept { return m_value >= other; }

	inline constexpr TypeCode GetTypeCode() const noexcept override { return TypeCode::Int32; };
	inline int GetHashCode() const override;
	inline int CompareTo(const Object* const obj) const override;
	inline int CompareTo(const Int32* const value) const override;
	inline bool Equals(const Object* const obj) const override;
	inline bool Equals(const Int32* const value) const override;
	//OVERRIDE OBJECT TO STRING inline const std::string ToString() const noexcept;
	//inline String ToString() const noexcept override;
	Boolean ToBoolean(IFormatProvider* provider) const override;
	Int16 ToInt16(IFormatProvider* provider) const override;
	Int32 ToInt32(IFormatProvider* provider) const override;

	static constexpr Int32 MaxValue() { return Int32(0x7FFFFFFF); }
	static constexpr Int32 MinValue() { return Int32(static_cast<int>(0x80000000)); }
};

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator+(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs + rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator-(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs - rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator*(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs - rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator/(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs / rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator%(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs % rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator&(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs & rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator|(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs | rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator^(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs ^ rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator<<(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs << rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr Int32 operator>>(T const& lhs, Int32 const& rhs) noexcept
{
	return Int32(lhs >> rhs.Get());
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value>>
constexpr bool operator==(T const& lhs, Int32 const& rhs) noexcept
{
	return lhs == rhs.Get();
}

template<typename T, std::is_fundamental<T>::value>
constexpr bool operator!=(T const& lhs, Int32 const& rhs) noexcept
{
	return lhs != rhs.Get();
}

template<typename T, std::is_fundamental<T>::value>
constexpr bool operator<(T const& lhs, Int32 const& rhs) noexcept
{
	return lhs < rhs.Get();
}

template<typename T, std::is_fundamental<T>::value>
constexpr bool operator<=(T const& lhs, Int32 const& rhs) noexcept
{
	return lhs < rhs.Get();
}

template<typename T, std::is_fundamental<T>::value>
constexpr bool operator>(T const& lhs, Int32 const& rhs) noexcept
{
	return lhs > rhs.Get();
}

template<typename T, std::is_fundamental<T>::value>
constexpr bool operator>=(T const& lhs, Int32 const& rhs) noexcept
{
	return lhs >= rhs.Get();
}