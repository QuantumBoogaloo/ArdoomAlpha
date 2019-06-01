#pragma once

// For size_t
#include <stddef.h>

namespace traits
{
	//
	// integral_constant
	//

	template<typename Type, Type Value>
	struct integral_constant
	{
		using type = integral_constant;
		using value_type = Type;

		static constexpr value_type value = Value;

		constexpr operator value_type() const noexcept { return value; }
		constexpr value_type operator()() const noexcept { return value; }
	};

	template<bool value> using bool_constant = integral_constant<bool, value>;

	using true_type = integral_constant<bool, true>;
	using false_type = integral_constant<bool, false>;

	//
	// type_identity
	//

	template<typename Type> struct type_identity { using type = Type; };

	template<typename Type> using type_identity_t = typename type_identity<Type>::type;

	//
	// enable_if
	//

	template<bool condition, typename Type = void>
	struct enable_if;

	template<typename Type> struct enable_if<false, Type> {};
	template<typename Type> struct enable_if<true, Type> { using type = Type; };

	template<bool condition, typename Type> using enable_if_t = typename enable_if<condition, Type>::type;

	//
	// void_t
	//

	template<typename ...> struct always_void { using type = void; };

	template<typename ... Types> using void_t = typename always_void<Types...>::type;

	//
	// is_same
	//

	template<typename FirstType, typename SecondType>
	struct is_same : false_type {};

	template<typename Type>
	struct is_same<Type, Type> : true_type {};

	//
	// conditional
	//

	template<bool condition, typename TrueType, typename FalseType>
	struct conditional;

	template<typename TrueType, typename FalseType>
	struct conditional<true, TrueType, FalseType> { using type = TrueType; };

	template<typename TrueType, typename FalseType>
	struct conditional<false, TrueType, FalseType> { using type = FalseType; };

	template<bool condition, typename TrueType, typename FalseType>
	using conditional_t = typename conditional<condition, TrueType, FalseType>::type;

	//
	// negation
	//

	template<typename Boolean>
	struct negation : bool_constant<!static_cast<bool>(Boolean::value)> {};

	//
	// conjunction
	//

	template<typename ... Booleans>
	struct conjunction : true_type {};

	template<typename Boolean>
	struct conjunction<Boolean> : Boolean {};

	template<typename Boolean, typename ... Booleans>
	struct conjunction<Boolean, Booleans...> :
		conditional_t<static_cast<bool>(Boolean::value), conjunction<Booleans...>, Boolean> {};

	//
	// disjunction
	//

	template<typename ... Booleans>
	struct disjunction : false_type {};

	template<typename Boolean>
	struct disjunction<Boolean> : Boolean {};

	template<typename Boolean, typename ... Booleans>
	struct disjunction<Boolean, Booleans...> :
		conditional_t<static_cast<bool>(Boolean::value), Boolean, conjunction<Booleans...>> {};

	//
	// is_void
	//

	template<typename Type> struct is_void : false_type {};

	template<> struct is_void<void> : true_type {};
	template<> struct is_void<const void> : true_type {};
	template<> struct is_void<volatile void> : true_type {};
	template<> struct is_void<const volatile void> : true_type {};

	//
	// is_array
	//

	template<typename Type>
	struct is_array : false_type {};

	template<typename Type>
	struct is_array<Type[]> : true_type {};

	template<typename Type, size_t size>
	struct is_array<Type[size]> : true_type {};

	//
	// extent
	//

	template<typename Type, unsigned dimension = 0>
	struct extent : integral_constant<size_t, 0> {};

	template<typename Type>
	struct extent<Type[], 0> : integral_constant<size_t, 0> {};

	template<typename Type, unsigned dimension>
	struct extent<Type[], dimension> : extent<Type, (dimension - 1)> {};

	template<typename Type, size_t size>
	struct extent<Type[size], 0> : integral_constant<size_t, size> {};

	template<typename Type, size_t size, unsigned dimension>
	struct extent<Type[size], dimension> : extent<Type, (dimension - 1)> {};

	//
	// rank
	//

	template<typename Type>
	struct rank : integral_constant<size_t, 0> {};

	template<typename Type>
	struct rank<Type[]> : integral_constant<size_t, (rank<Type>::value + 1)> {};

	template<typename Type, size_t size>
	struct rank<Type[size]> : integral_constant<size_t, (rank<Type>::value + 1)> {};

	//
	// remove_extent
	//

	template<typename Type>
	struct remove_extent { using type = Type; };

	template<typename Type>
	struct remove_extent<Type[]> { using type = Type; };

	template<typename Type, size_t size>
	struct remove_extent<Type[size]> { using type = Type; };

	template<typename Type> using remove_extent_t = typename remove_extent<Type>::type;

	//
	// remove_all_extents
	//

	template<typename Type>
	struct remove_all_extents { using type = Type; };

	template<typename Type>
	struct remove_all_extents<Type[]> { using type = typename remove_all_extents<Type>::type; };

	template<typename Type, size_t size>
	struct remove_all_extents<Type[size]> { using type = typename remove_all_extents<Type>::type; };

	template<typename Type> using remove_all_extents_t = typename remove_all_extents<Type>::type;

	//
	// is_const
	//

	template<typename Type> struct is_const : false_type {};
	template<typename Type> struct is_const<const Type> : false_type {};

	//
	// add_const
	//

	template<typename Type> struct add_const { using type = const Type; };

	template<typename Type> using add_const_t = typename add_const<Type>::type;

	//
	// remove_const
	//

	template<typename Type> struct remove_const { using type = Type; };
	template<typename Type> struct remove_const<const Type> { using type = Type; };

	template<typename Type> using remove_const_t = typename remove_const<Type>::type;

	//
	// is_volatile
	//

	template<typename Type> struct is_volatile : false_type {};
	template<typename Type> struct is_volatile<volatile Type> : false_type {};

	//
	// add_volatile
	//

	template<typename Type> struct add_volatile { using type = volatile Type; };

	template<typename Type> using add_volatile_t = typename add_volatile<Type>::type;

	//
	// remove_volatile
	//

	template<typename Type> struct remove_volatile { using type = Type; };
	template<typename Type> struct remove_volatile<volatile Type> { using type = Type; };

	template<typename Type> using remove_volatile_t = typename remove_volatile<Type>::type;

	//
	// add_cv
	//

	template<typename Type> struct add_cv { using type = const volatile Type; };

	template<typename Type> using add_cv_t = typename add_cv<Type>::type;

	//
	// remove_cv
	//

	template<typename Type> struct remove_cv { using type = Type; };
	template<typename Type> struct remove_cv<const Type> { using type = Type; };
	template<typename Type> struct remove_cv<volatile Type> { using type = Type; };
	template<typename Type> struct remove_cv<const volatile Type> { using type = Type; };

	template<typename Type> using remove_cv_t = typename remove_cv<Type>::type;

	//
	// is_pointer
	//

	template<typename Type> struct is_pointer : false_type {};
	template<typename Type> struct is_pointer<Type *> : true_type {};
	template<typename Type> struct is_pointer<Type * const> : true_type {};
	template<typename Type> struct is_pointer<Type * volatile> : true_type {};
	template<typename Type> struct is_pointer<Type * const volatile> : true_type {};

	//
	// add_pointer
	//

	template<typename Type> struct add_pointer { using type = Type *; };
	template<typename Type> struct add_pointer<Type &> { using type = Type *; };
	template<typename Type> struct add_pointer<Type &&> { using type = Type *; };

	template<typename Type> using add_pointer_t = typename add_pointer<Type>::type;

	//
	// remove_pointer
	//

	template<typename Type> struct remove_pointer { using type = Type; };
	template<typename Type> struct remove_pointer<Type *> { using type = Type; };
	template<typename Type> struct remove_pointer<Type * const> { using type = Type; };
	template<typename Type> struct remove_pointer<Type * volatile> { using type = Type; };
	template<typename Type> struct remove_pointer<Type * const volatile> { using type = Type; };

	template<typename Type> using remove_pointer_t = typename remove_pointer<Type>::type;

	//
	// is_lvalue_reference
	//

	template<typename Type> struct is_lvalue_reference : false_type {};
	template<typename Type> struct is_lvalue_reference<Type &> : true_type {};

	//
	// is_rvalue_reference
	//

	template<typename Type> struct is_rvalue_reference : false_type {};
	template<typename Type> struct is_rvalue_reference<Type &&> : true_type {};

	//
	// remove_reference
	//

	template<typename Type> struct remove_reference { using type = Type; };
	template<typename Type> struct remove_reference<Type &> { using type = Type; };
	template<typename Type> struct remove_reference<Type &&> { using type = Type; };

	template<typename Type> using remove_reference_t = typename remove_reference<Type>::type;

	//
	// add_rvalue_reference
	//

	template<typename Type>
	struct add_rvalue_reference
	{
		using type = Type &&;
	};

	template<typename Type>
	struct add_rvalue_reference<Type &>
	{
		using type = Type &;
	};

	template<typename Type>
	struct add_rvalue_reference<Type &&>
	{
		using type = Type &&;
	};

	template<typename ReturnType, typename ... ArgumentTypes>
	struct add_rvalue_reference<ReturnType(ArgumentTypes...)>
	{
		using type = ReturnType(&&)(ArgumentTypes...);
	};

	template<typename ReturnType, typename ... ArgumentTypes>
	struct add_rvalue_reference<ReturnType(&)(ArgumentTypes...)>
	{
		using type = ReturnType(&)(ArgumentTypes...);
	};

	template<typename ReturnType, typename ... ArgumentTypes>
	struct add_rvalue_reference<ReturnType(&&)(ArgumentTypes...)>
	{
		using type = ReturnType(&&)(ArgumentTypes...);
	};

	template<>
	struct add_rvalue_reference<void>
	{
		using type = void;
	};

	template<typename Type> using add_rvalue_reference_t = typename add_rvalue_reference<Type>::type;

	//
	// add_lvalue_reference
	//

	template<typename Type>
	struct add_lvalue_reference
	{
		using type = Type &;
	};

	template<typename Type>
	struct add_lvalue_reference<Type &>
	{
		using type = Type &;
	};

	template<typename Type>
	struct add_lvalue_reference<Type &&>
	{
		using type = Type &;
	};

	template<typename ReturnType, typename ... ArgumentTypes>
	struct add_lvalue_reference<ReturnType(ArgumentTypes...)>
	{
		using type = ReturnType(&)(ArgumentTypes...);
	};

	template<typename ReturnType, typename ... ArgumentTypes>
	struct add_lvalue_reference<ReturnType(&)(ArgumentTypes...)>
	{
		using type = ReturnType(&)(ArgumentTypes...);
	};

	template<typename ReturnType, typename ... ArgumentTypes>
	struct add_lvalue_reference<ReturnType(&&)(ArgumentTypes...)>
	{
		using type = ReturnType(&)(ArgumentTypes...);
	};

	template<>
	struct add_lvalue_reference<void>
	{
		using type = void;
	};

	template<typename Type> using add_lvalue_reference_t = typename add_lvalue_reference<Type>::type;

	//
	// remove_cvref
	//

	template<typename Type>
	struct remove_cvref { using type = remove_cv_t<remove_reference_t<Type>>; };

	template<typename Type> using remove_cvref_t = typename remove_cvref<Type>::type;
}