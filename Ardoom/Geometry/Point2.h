#pragma once

#include "Vector2.h"

template<typename Type>
struct Point2
{
	using ValueType = Type;

	ValueType x;
	ValueType y;

	Point2() = default;
	Point2(ValueType x, ValueType y) :
		x(x), y(y)
	{
	}

	/// Adds a vector to this point.
	Point2 & operator +=(const Vector2<Type> & other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	/// Subtracts a vector from this point.
	Point2 & operator -=(const Vector2<Type> & other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	/// Converts a Point2 to another kind of Point2.
	template<typename OtherType>
	explicit operator Point2<OtherType>() const
	{
		return { static_cast<OtherType>(this->x), static_cast<OtherType>(this->y) };
	}
};

/// Checks if two points are equal.
template<typename Type>
constexpr bool operator ==(const Point2<Type> & left, const Point2<Type> & right)
{
	return ((left.x == right.x) && (left.y == right.y));
}

/// Checks if two points are not equal.
template<typename Type>
constexpr bool operator !=(const Point2<Type> & left, const Point2<Type> & right)
{
	return ((left.x != right.x) || (left.y != right.y));
}

/// Adds a vector to a point.
template<typename Type>
constexpr Point2<Type> operator +(const Point2<Type> & left, const Vector2<Type> & right)
{
	return { (left.x + right.x), (left.y + right.y) };
}

/// Subtracts a vector from a point.
template<typename Type>
constexpr Point2<Type> operator -(const Point2<Type> & left, const Vector2<Type> & right)
{
	return { (left.x - right.x), (left.y - right.y) };
}

/// Subtracts a point from a point, thus retrieving the vector between the two points.
template<typename Type>
constexpr Vector2<Type> operator -(const Point2<Type> & left, const Point2<Type> & right)
{
	return { (left.x - right.x), (left.y - right.y) };
}

/// Gets the distance between two points.
template<typename Type>
constexpr auto distance(const Point2<Type> & left, const Point2<Type> & right) -> decltype((right - left).magnitude())
{
	return (right - left).magnitude();
}

/// Gets the square distance between two points.
template<typename Type>
constexpr auto distanceSquared(const Point2<Type> & left, const Point2<Type> & right) -> decltype((right - left).magnitudeSquared())
{
	return (right - left).magnitudeSquared();
}