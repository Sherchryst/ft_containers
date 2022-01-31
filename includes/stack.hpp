/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:04:10 by sgah              #+#    #+#             */
/*   Updated: 2022/01/31 03:19:41 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef std::size_t		size_type;

			explicit stack(const container_type &cont = container_type()) : c(cont){}
			stack(const stack& src): c(src.c){}
			~stack(){}

			stack operator=(const stack &rhs)
			{
				c = rhs.c;
				return *this;
			}

			bool empty(void) const
			{
				return c.empty();
			}

			size_type size(void) const
			{
				return c.size();
			}

			value_type &top(void)
			{
				return c.back();
			}

			const value_type &top(void) const
			{
				return c.back();
			}

			void push(const value_type &u)
			{
				c.push_back(u);
			}

			void pop(void)
			{
				c.pop_back();
			}

			template <class U, class ctnr>
			friend bool operator==(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

			template <class U, class ctnr>
			friend bool operator!=(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

			template <class U, class ctnr>
			friend bool operator<(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

			template <class U, class ctnr>
			friend bool operator<=(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

			template <class U, class ctnr>
			friend bool operator>(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

			template <class U, class ctnr>
			friend bool operator>=(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

		protected:
			container_type c;

	};

	template <class T, class Container>
	bool operator==(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T, class Container>
	bool operator<(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator>=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
}
