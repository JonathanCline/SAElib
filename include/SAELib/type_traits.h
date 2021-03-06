#pragma once
#ifndef SAELIB_TYPE_TRAITS_H
#define SAELIB_TYPE_TRAITS_H

/*
	Copyright 2021 Jonathan Cline
	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
	(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
	publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
	Contains any using directives for standard library type traits used in SAELib along with SAELib specific type traits
*/

#include "SAELib/config.h"

#if (SAELIB_CXX_STANDARD >= 11)

#include <type_traits>
#include <limits>
#include <utility>

namespace sae
{

	/*
		Type comparison
	*/

	using std::is_same;
	using std::is_same_v;

	using std::is_convertible;
	using std::is_convertible_v;



	template <typename T, typename... Ts>
	struct is_any_of : std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};

	template <typename T, typename... Ts>
	SAELIB_CONSTEXPR static bool is_any_of_v = is_any_of<T, Ts...>::value;


	/*
		Character type traits
	*/


	template <typename T>
	struct is_character : public is_any_of<T,
		unsigned char,
		char
#if SAELIB_CXX_STANDARD >= 20
		,
		wchar_t,
		char8_t,
		char16_t,
		char32_t
#endif
	> {};

	template <typename T>
	SAELIB_CONSTEXPR static bool is_character_v = is_character<T>::value;

	/*
		Basic type catagory
	*/

	using std::is_fundamental;
	using std::is_fundamental_v;

	using std::is_integral;
	using std::is_integral_v;

	using std::is_arithmetic;
	using std::is_arithmetic_v;

	using std::is_floating_point;
	using std::is_floating_point_v;

	using std::is_signed;
	using std::is_signed_v;

	using std::is_unsigned;
	using std::is_unsigned_v;

	template <typename T>
	SAELIB_CONSTEXPR static bool is_integer_v = is_arithmetic_v<T> && std::numeric_limits<T>::is_integer;

	template <typename T>
	struct is_integer : public std::bool_constant<is_integer_v<T>> {};








	/*
		Constructor related
	*/

	using std::is_constructible;
	using std::is_constructible_v;

	using std::is_copy_constructible;
	using std::is_copy_constructible_v;

	using std::is_copy_assignable;
	using std::is_copy_assignable_v;

	using std::is_move_constructible;
	using std::is_move_constructible_v;

	using std::is_move_assignable;
	using std::is_move_assignable_v;

	using std::is_default_constructible;
	using std::is_default_constructible_v;



	/*
		Trivial type
	*/

	using std::is_trivially_default_constructible;
	using std::is_trivially_default_constructible_v;

	using std::is_trivially_copy_constructible;
	using std::is_trivially_copy_constructible_v;

	using std::is_trivially_copy_assignable;
	using std::is_trivially_copy_assignable_v;

	using std::is_trivially_copyable;
	using std::is_trivially_copyable_v;

	using std::is_trivially_move_constructible;
	using std::is_trivially_move_constructible_v;

	using std::is_trivially_move_assignable;
	using std::is_trivially_move_assignable_v;



	template <typename T>
	SAELIB_CONSTEXPR static bool is_trivially_moveable_v = is_trivially_move_assignable_v<T> && is_trivially_move_constructible_v<T>;

	template <typename T>
	struct is_trivially_moveable : public std::bool_constant<is_trivially_moveable_v<T>> {};

	using std::is_trivially_assignable;
	using std::is_trivially_assignable_v;



	using std::is_trivially_constructible;
	using std::is_trivially_constructible_v;

	using std::is_trivially_default_constructible;
	using std::is_trivially_default_constructible_v;

	using std::is_trivial;
	using std::is_trivial_v;




	template <typename From, typename To>
	SAELIB_CONSTEXPR static bool is_forwardable_to_v = is_constructible_v<To, std::remove_reference_t<From>>;

	template <typename From, typename To>
	struct is_forwardable_to : public std::bool_constant<is_forwardable_to_v<From, To>> {};


	/*
		Function related
	*/

	using std::is_function;
	using std::is_function_v;

	template <typename T, typename = void>
	struct is_function_pointer : public std::false_type {};

	template <typename RetT, typename... Args>
	struct is_function_pointer<RetT(*)(Args...), void> : public std::true_type {};

	template <typename RetT, typename ScopeT, typename... Args>
	struct is_function_pointer<RetT(ScopeT::*)(Args...), void> : public std::true_type {};

	template <typename T>
	SAELIB_CONSTEXPR static bool is_function_pointer_v = is_function_pointer<T>::value;



	/*
		Member function pointer
	*/

	using std::is_member_function_pointer;
	using std::is_member_function_pointer_v;



	/*
		Free function pointer
	*/

	template <typename T>
	SAELIB_CONSTEXPR static bool is_free_function_pointer_v = is_function_pointer_v<T> && (!is_member_function_pointer_v<T>);

	template <typename T>
	struct is_free_function_pointer : std::bool_constant<is_free_function_pointer_v<T>> {};



};

#endif

#endif