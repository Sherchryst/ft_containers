/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:38:55 by sgah              #+#    #+#             */
/*   Updated: 2021/11/17 17:04:07 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
/**========================================================================
 **                          FT::ENABLE IF
 *?  If B is true, ft::enable_if has a public member typedef type,
 *?  equal to T; otherwise, there is no member typedef.
 *========================================================================**/
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };
/*============================ END OF FT::ENABLE_IF ============================*/

/**========================================================================
 **                           FT::IS_INTEGRAL
 *?  Checks whether T is an integral type. Provides the member constant value
 *?  which is equal to true, if T is the type:
**  - bool
**  - char
**  - char16_t
**  - char32_t
**  - wchar_t
**  - signed char
**  - short int
**  - int
**  - long int
**  - long long int
**  - unsigned char
**  - unsigned short int
**  - unsigned int
**  - unsigned long int
**  - unsigned long long int
 *?  Otherwise, value is equal to false.
 *========================================================================**/
	template <bool is_integral, typename T>
	struct is_integral_base
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
	struct is_integral_type : public is_integral_base<false, bool> {};

	template <>
	struct is_integral_type<bool>: public is_integral_base<true, bool> {};

	template <>
	struct is_integral_type<char>: public is_integral_base<true, char> {};

	template <>
	struct is_integral_type<signed char>: public is_integral_base<true, signed char> {};

	template <>
	struct is_integral_type<short int>: public is_integral_base<true, short int> {};

	template <>
	struct is_integral_type<int>: public is_integral_base<true, int> {};

	template <>
	struct is_integral_type<long int>: public is_integral_base<true, long int> {};

	template <>
	struct is_integral_type<long long int>: public is_integral_base<true, long long int> {};

	template <>
	struct is_integral_type<unsigned char>: public is_integral_base<true, unsigned char> {};

	template <>
	struct is_integral_type<unsigned short int>: public is_integral_base<true, unsigned short int> {};

	template <>
	struct is_integral_type<unsigned int>: public is_integral_base<true, unsigned int> {};

	template <>
	struct is_integral_type<unsigned long int>: public is_integral_base<true, unsigned long int> {};

	template <>
	struct is_integral_type<unsigned long long int>: public is_integral_base<true, unsigned long long int> {};

	template <typename T>
	struct is_integral : public is_integral_type<T> {};
/*============================ END OF FT::IS_INTEGRAL ============================*/

/**========================================================================
 **                           FT::PAIR
 *?  Put in couple a pair of value that can be different
 *@param Class T1
 *@param Class T2
 *========================================================================**/
	template <class T1, class T2>
	struct pair
	{
		public :
			typedef T1 first_type;

			typedef T2 second_type;

			first_type first;

			second_type second;

			pair():first(), second() {}

			template<class U, class V>
			pair(const pair<U, V>& p):first(p.first), second(p.second) {}

			pair(const first_type& a, const second_type& b):first(a), second(b) {}

			pair& operator= (const pair& p)
			{
				this->first = p.first;
				this->second = p.second;
				return (*this);
			}
	};

	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}
/*============================ END OF FT::PAIR ============================*/

}
