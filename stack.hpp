/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:04:10 by sgah              #+#    #+#             */
/*   Updated: 2022/01/26 15:20:58 by sgah             ###   ########.fr       */
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

			explicit stack(const container_type &cont = container_type()) : _container(cont){}
			stack(const stack& src): _container(src._container){}
			~stack() {}

			// = operator overload
			stack operator=(const stack &rhs)
			{
				if (this != &rhs)
				{
					_container = rhs._container;
				}
				return *this;
			}

			bool empty(void) const
			{
				return _container.empty();
			}

			size_type size(void) const
			{
				return _container.size();
			}

			value_type &top(void)
			{
				return _container.back();
			}

			const value_type &top(void) const
			{
				return _container.back();
			}

			void push(const value_type &u)
			{
				_container.push_back(u);
			}

			void pop(void)
			{
				_container.pop_back();
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

		private:
			container_type _container;

	};

	template <class T, class Container>
	bool operator==(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs._container == rhs._container);
	}

	template <class T, class Container>
	bool operator!=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs._container != rhs._container);
	}

	template <class T, class Container>
	bool operator<(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs._container < rhs._container);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs._container <= rhs._container);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs._container > rhs._container);
	}

	template <class T, class Container>
	bool operator>=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
	{
		return (lhs._container >= rhs._container);
	}
}
