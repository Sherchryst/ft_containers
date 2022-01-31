/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:35:18 by sgah              #+#    #+#             */
/*   Updated: 2022/01/31 03:46:12 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <memory>
# include <limits>
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T> >
	class vector {

		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::size_type				size_type;

			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<value_type const>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:

			allocator_type	_alloc;
			pointer			_first;
			pointer			_last;
			pointer			_endalloc;
			size_type		_capacity;
			size_type		_size;

			void reAlloc(size_type n)
			{
				pointer ptr = _alloc.allocate(n);

				for (size_type i = 0; i < _size; i++)
					_alloc.construct(ptr + i, *(_first + i));
				this->~vector();

				_first = ptr;
				_capacity = n;
			}

		public:

			explicit vector(const Allocator& alloc = Allocator()):
			_alloc(alloc), _first(NULL), _last(NULL), _endalloc(NULL), _capacity(0), _size(0){}

			explicit vector(size_type n, const T& value = T(),const Allocator& alloc = Allocator()):
			_alloc(alloc), _first(NULL), _last(NULL), _endalloc(NULL), _capacity(n), _size(n)
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
			vector(InputIterator first, InputIterator last,
			const Allocator& alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
			_alloc(alloc)
			{
				size_type dist = 0;

				for (InputIterator it = first; it != last; dist++, it++);
				_capacity = dist;
				_size = dist;
				_first = _alloc.allocate(_size);
				_endalloc = _first + dist;
				_last = _first;
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(_last, *first++);
					_last++;
				}
			}

			vector(const vector<T,Allocator>& src):
			_alloc(src._alloc), _first(src._first), _last(src._last), _endalloc(src._endalloc), _capacity(src._capacity), _size(src._size)
			{
				_first = _alloc.allocate(_capacity);
				_endalloc = _first + _capacity;
				_last = _first;
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(_last, *(src._first + i));
					_last++;
				}
			}

			~vector(void)
			{
				for (iterator it = _first; it != end(); it++)
					_alloc.destroy(&(*it));
				_alloc.deallocate(_first, _capacity);
			}

			vector& operator=(const vector& src)
			{
				if (this != &src)
				{
					this->~vector();
					_size = src._size;
					if (_size > _capacity)
						_capacity = src._size;
					_first = _alloc.allocate(_capacity);
					_endalloc = _first + _capacity;
					_last = _first;
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(_last, *(src._first + i));
						_last++;
					}
				}
				return (*this);
			}

			template <class InputIterator>
			void assign (typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last)
			{
				size_type dist = 0;

				for (InputIterator it = first; it != last; it++, dist++);
				if (dist > _capacity)
				{
					this->~vector();
					_size = 0;
					_capacity = dist;
					_first = _alloc.allocate(_capacity);
					_endalloc = _first + _capacity;
					_last = _first;
					while (first != last)
					{
						_alloc.construct(_last, *first++);
						_last++;
						_size++;
					}
				}
				else
				{
					clear();
					while (first != last)
						_alloc.construct(_first + _size++, *first++);
				}
			}

			void assign(size_type n, const value_type& u)
			{
				if (n > _capacity)
				{
					this->~vector();
					_capacity = n;
					_size = n;
					_first = _alloc.allocate(_capacity);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_first + i, u);
				}
				else
				{
					clear();
					while (_size < n)
						_alloc.construct(_first + _size++, u);
				}
			}

			allocator_type get_allocator(void) const
			{
				return (_alloc);
			}

			iterator begin(void)
			{
				return (iterator(_first));
			}

			const_iterator begin(void) const
			{
				return (const_iterator(_first));
			}

			iterator end(void)
			{
				return (iterator(_first + _size));
			}

			const_iterator end(void) const
			{
				return (const_iterator(_first + _size));
			}

			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin(void) const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator rend(void)
			{
				return (reverse_iterator(_first));
			}

			const_reverse_iterator rend(void) const
			{
				return (const_reverse_iterator(_first));
			}

			size_type size(void) const
			{
				return (_size);
			}

			size_type max_size(void) const
			{
				return _alloc.max_size();
			}

			void resize(size_type sz, value_type c = value_type())
			{
				if (sz < _size)
				{
					while (sz < _size)
						_alloc.destroy(_first + --_size);
					_last = _first + _size;
				}
				else
				{
					if (sz > _capacity * 2)
						reserve(sz);
					else if (sz > _capacity)
						reserve(_capacity * 2);
					while (_size != sz)
						push_back(c);
				}
			}

			size_type capacity(void) const
			{
				return (_capacity);
			}

			bool empty() const
			{
				return (_size == 0);
			}

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("std::bad_allocmaking");
				if (n > _capacity)
					reAlloc(n);
			}

			reference operator[](size_type n)
			{
				return (_first[n]);
			}

			const_reference operator[](size_type n) const
			{
				return (_first[n]);
			}

			reference at (size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("vector::n out of range");
				return (_first[n]);
			}

			const_reference at (size_type n) const
			{
				if (n > this->_size)
					throw std::out_of_range("vector::n out of range");
				return _first[n];
			}

			reference front(void)
			{
				return (_first[0]);
			}

			const_reference front(void) const
			{
				return (_first[0]);
			}

			reference back(void)
			{
				return (_first[_size - 1]);
			}

			const_reference back(void) const
			{
				return (_first[_size - 1]);
			}

			void push_back(const value_type& x)
			{
				if (_size == _capacity)
					resize(_size + 1, x);
				else
					_alloc.construct(_first + _size++, x);
			}

			void pop_back(void)
			{
				_alloc.destroy(&_first[--_size]);
			}

			iterator insert(iterator position, const value_type& x)
			{
				difference_type diff = position - begin();

				insert(position, 1, x);
				return (iterator(begin() + diff));
			}

			void insert(iterator position, size_type n, const value_type& x)
			{
				difference_type const diff = position - begin();
				difference_type const end_diff = end() - begin();
				iterator old_end;
				iterator new_end;

				resize(_size + n);
				new_end = end();
				position = begin() + diff;
				old_end = begin() + end_diff;
				while (old_end != position)
					*--new_end = *--old_end;
				while (n-- > 0)
					*position++ = x;
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last)
			{
				difference_type const diff = position - begin();
				difference_type const end_diff = end() - begin();
				iterator old_end;
				iterator new_end;
				difference_type n = 0;

				for (InputIterator tmp = first; tmp != last; tmp++, n++);
				resize(_size + n);
				new_end = end();
				position = begin() + diff;
				old_end = begin() + end_diff;
				while (old_end != position)
					*--new_end = *--old_end;
				while (first != last)
					*position++ = *first++;
			}

			iterator erase(iterator position)
			{
				_alloc.destroy(&*position);

				for (iterator it = position; it + 1 != end(); it++)
				{
					_alloc.construct(&*it, *(it + 1));
					_alloc.destroy(&*it + 1);
				}
				_size--;
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				difference_type diff = last - first;
				for (iterator it = first; it != last; it++)
					_alloc.destroy(&*it);
				for (iterator it = first; it + diff != end(); it++)
				{
					_alloc.construct(&*it, *(it + diff));
					_alloc.destroy(&*(it + diff));
				}
				_size -= diff;
				return first;
			}

			void swap(vector& x)
			{
				pointer tmp = _first;
				_first = x._first;
				x._first = tmp;

				size_type tmp_size = _size;
				_size = x._size;
				x._size = tmp_size;

				size_type tmp_capacity = _capacity;
				_capacity = x._capacity;
				x._capacity = tmp_capacity;
			}

			void clear(void)
			{
				while (!empty())
					pop_back();
			}
	};
	template<class T, class A>
	bool operator==(const vector<T, A> &lhs, const vector<T, A> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class T, class A>
	bool operator!=(const vector<T, A> &lhs, const vector<T, A> &rhs)
	{
		return !(rhs == lhs);
	}

	template<class T, class A>
	bool operator<(const vector<T, A> &lhs, const vector<T, A> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class A>
	bool operator<=(const vector<T, A> &lhs, const vector<T, A> &rhs)
	{
		return !(rhs < lhs);
	}

	template<class T, class A>
	bool operator>(const vector<T, A> &lhs, const vector<T, A> &rhs)
	{
		return (rhs < lhs);
	}

	template<class T, class A>
	bool operator>=(const vector<T, A> &lhs, const vector<T, A> &rhs)
	{
		return !(lhs < rhs);
	}

	template<class T, class A>
	void swap(vector<T, A>& lhs, vector<T, A>& rhs)
	{
		lhs.swap(rhs);
	}
}
