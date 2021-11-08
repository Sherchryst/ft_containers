/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:35:18 by sgah              #+#    #+#             */
/*   Updated: 2021/11/08 17:42:09 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>
# include <algorithm>
# include <cstddef>
# include "type_traits.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T> >
	class vector {

		public:

			typedef typename Allocator::reference reference;

			typedef typename Allocator::const_reference const_reference;

			typedef implementation defined iterator; // See 23.1

			typedef implementation defined const_iterator; // See 23.1

			typedef std::size_t size_type; // See 23.1

			typedef std::ptrdiff_t difference_type;// See 23

			typedef T value_type;

			typedef Allocator allocator_type;

			typedef typename Allocator::pointer pointer;

			typedef typename Allocator::const_pointer const_pointer;

			typedef std::reverse_iterator<iterator> reverse_iterator;

			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		private:

			allocator_type	_alloc;
			pointer			_first;
			pointer			_last;
			pointer			_endalloc;

		public:

			explicit vector(const Allocator& alloc = Allocator()):
			_alloc(alloc), _first(nullptr), _last(nullptr), _endalloc(nullptr){}

			explicit vector(size_type n, const T& value = T(),const Allocator& alloc = Allocator()):
			:_alloc(alloc), _first(nullptr), _last(nullptr), _endalloc(nullptr)
			{
				_first = _alloc.allocate(n);
				_endalloc = _first + n;
				_last = _first;
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(_last, value);
					_last++;
				}
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator());

			vector(const vector<T,Allocator>& src): _alloc(allocator_type())
			{
				*this = src;
			}

			~vector();

			vector<T,Allocator>& operator=(const vector<T,Allocator>& x);

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);

			void assign(size_type n, const T& u);
			allocator_type get_allocator() const;
			// iterators:
			iterator begin()
			{
				return (_start);
			}
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			// 23.2.4.2 capacity:
			size_type size() const;
			size_type max_size() const;
			void resize(size_type sz, T c = T());
			size_type capacity() const;
			bool empty() const;
			void reserve(size_type n);
			// element access:
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			// 23.2.4.3 modifiers:
			void push_back(const T& x);
			void pop_back();
			iterator insert(iterator position, const T& x);
			void insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector<T,Allocator>&);
			void clear();
	};
	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x,
	const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x,
	const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x,
	const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x,
	const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x,
	const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x,
	const vector<T,Allocator>& y);
	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}
