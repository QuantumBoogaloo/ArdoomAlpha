#pragma once

// For size_t
#include <stddef.h>

// For remove_reference_t
#include "Traits.h"

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

namespace utils
{
	//
	// <utility>
	//

	template<typename Type>
	traits::add_rvalue_reference_t<Type> declval(traits::remove_reference_t<Type> & value) noexcept;

	template<typename Type>
	constexpr auto move(Type && value) noexcept -> traits::remove_reference_t<Type> &&
	{
		return static_cast<traits::remove_reference_t<Type>>(value);
	}

	template<typename Type>
	constexpr Type && forward(traits::remove_reference_t<Type> & value) noexcept
	{
		return static_cast<Type&&>(value);
	}

	template<typename Type>
	constexpr Type && forward(traits::remove_reference_t<Type> && value) noexcept
	{
		static_assert(traits::is_lvalue_reference<Type>::value, "Cannot forward an rvalue as an lvalue");
		return static_cast<Type&&>(value);
	}

	template<typename Type>
	void swap(Type & left, Type & right)
	{
		Type temporary = utils::move(left);
		left = utils::move(right);
		right = utils::move(temporary);
	}

	template<typename Type, size_t size>
	void swap(Type (&left)[size], Type (&right)[size]) noexcept(noexcept(swap(left[0], right[0])))
	{
		using utils::swap;
		for(size_t index = 0; index < size; ++index)
			swap(left[index], right[index]);
	}

	template<typename Type, typename OtherType = Type>
	Type exchange(Type & object, OtherType && newValue) noexcept
	{
		Type oldValue = move(object);
		object = forward(newValue);
		return oldValue;
	}

	//
	// <algorithm>
	//

	template<typename Type>
	constexpr const Type & min(const Type & left, const Type & right)
	{
		return (left < right) ? left : right;
	}

	template<typename Type, typename Comparer>
	constexpr const Type & min(const Type & left, const Type & right, Comparer comparer)
	{
		return comparer(left, right) ? left : right;
	}

	template<typename Type>
	constexpr const Type & max(const Type & left, const Type & right)
	{
		return (left < right) ? right : left;
	}

	template<typename Type, typename Comparer>
	constexpr const Type & max(const Type & left, const Type & right, Comparer comparer)
	{
		return comparer(left, right) ? right : left;
	}

	template<typename Type>
	constexpr const Type & clamp(const Type & value, const Type & minimum, const Type & maximum)
	{
		return (value < minimum) ? minimum : (maximum < value) ? maximum : value;
	}

	template<typename Type, typename Comparer>
	constexpr const Type & clamp(const Type & value, const Type & minimum, const Type & maximum, Comparer comparer)
	{
		return comparer(value, minimum) ? minimum : comparer(maximum, value) ? maximum : value;
	}
}