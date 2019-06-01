#pragma once

template<typename Type>
struct Vector2
{
	using ValueType = Type;

	ValueType x;
	ValueType y;

	Vector2() = default;
	Vector2(ValueType x, ValueType y) :
		x{x}, y{y}
	{
	}

	constexpr auto magnitudeSquared() const -> decltype((x * x) + (y * y))
	{
		return ((x * x) + (y * y));
	}

	auto magnitude() const -> decltype(sqrt(magnitudeSquared()))
	{
		return sqrt(magnitudeSquared());
	}

	constexpr bool isZeroLength() const
	{
		return ((this->x == 0) && (this->y == 0));
	}

	/// Adds another vector to this vector.
	Vector2 & operator +=(const Vector2 & other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	/// Subtracts another vector from this vector.
	Vector2 & operator -=(const Vector2 & other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	/// Multiplies this vector by the given value.
	Vector2 & operator *=(ValueType value)
	{
		this->x *= value;
		this->y *= value;
		return *this;
	}

	/// Multiplies this vector by some value.
	template<typename OtherType>
	Vector2 & operator *=(OtherType value)
	{
		this->x *= value;
		this->y *= value;
		return *this;
	}

	/// Divides this vector by the given value.
	Vector2 & operator /=(ValueType value)
	{
		this->x /= value;
		this->y /= value;
		return *this;
	}

	/// Divides this vector by some value.
	template<typename OtherType>
	Vector2 & operator /=(OtherType value)
	{
		this->x *= value;
		this->y *= value;
		return *this;
	}

	/// Converts a Vector2 to another kind of Vector2.
	template<typename OtherType>
	explicit operator Vector2<OtherType>() const
	{
		return { static_cast<OtherType>(this->x), static_cast<OtherType>(this->y) };
	}
};

/// Checks if two vectors are equal.
template<typename Type>
constexpr bool operator ==(const Vector2<Type> & left, const Vector2<Type> & right)
{
	return ((left.x == right.x) && (left.y == right.y));
}

/// Checks if two vectors are not equal.
template<typename Type>
constexpr bool operator !=(const Vector2<Type> & left, const Vector2<Type> & right)
{
	return ((left.x != right.x) || (left.y != right.y));
}

/// Negates a vector.
template<typename Type>
constexpr Vector2<Type> operator -(const Vector2<Type> & vector)
{
	return { -vector.x, -vector.y };
}

/// Adds two vectors.
template<typename Type>
constexpr Vector2<Type> operator +(const Vector2<Type> & left, const Vector2<Type> & right)
{
	return { (left.x + right.x), (left.y + right.y) };
}

/// Subtracts two vectors.
template<typename Type>
constexpr Vector2<Type> operator -(const Vector2<Type> & left, const Vector2<Type> & right)
{
	return { (left.x - right.x), (left.y - right.y) };
}

/// Multiplies a vector by another type.
/// Return type is dependent on context.
template<typename Type, typename OtherType>
constexpr auto operator *(const Vector2<Type> & left, OtherType right) -> Vector2<decltype(left.x * right)>
{
	return { (left.x * right), (left.y * right) };
}

/// Multiplies a vector by another type.
/// Return type is dependent on context.
template<typename Type, typename OtherType>
constexpr auto operator *(OtherType left, const Vector2<Type> & right) -> Vector2<decltype(left * right.x)>
{
	return { (left * right.x), (left * right.y) };
}

/// Divides a vector by another type.
/// Return type is dependent on context.
template<typename Type, typename OtherType>
constexpr auto operator /(const Vector2<Type> & left, OtherType right) -> Vector2<decltype(left.x / right)>
{
	return { (left.x / right), (left.y / right) };
}

/// Creates a normalised version of the given vector.
/// The result type is inferred from the operation.
template<typename Type>
constexpr auto normalise(const Vector2<Type> & vector) -> Vector2<decltype(vector / vector.magnitude())>
{
	return (vector / vector.magnitude());
}

/// Creates a normalised version of the given vector.
/// Forces the magnitude back to Type first.
template<typename Type>
constexpr Vector2<Type> normaliseStrict(const Vector2<Type> & vector)
{
	return (vector / static_cast<Type>(vector.magnitude()));
}

/// Gets the dot product of two vectors.
template<typename Type>
constexpr Type dotProduct(const Vector2<Type> & left, const Vector2<Type> & right)
{
	return ((left.x * right.x) + (left.y * right.y));
}