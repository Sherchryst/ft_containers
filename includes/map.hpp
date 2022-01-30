/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 04:56:40 by sgah              #+#    #+#             */
/*   Updated: 2022/01/31 00:25:23 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include <memory>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare										key_compare;
			class												value_compare;
			typedef Alloc										allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;

		protected:
			typedef ft::red_black_tree<key_type, value_type, first_element<value_type, key_type>, key_compare>	tree_type;
			typedef Node<value_type>	node_type;
			typedef Node<value_type>*	node_ptr;

		public:
			typedef ft::bidirectional_iterator<value_type, node_type>				iterator;
			typedef ft::bidirectional_iterator<value_type const, node_type const>	const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		protected:
			key_compare		_comp;
			allocator_type	_alloc;
			tree_type		_binary_tree;

		public:
			map (const map& x)
			{
				insert(x.begin(), x.end());
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _comp(comp), _alloc(alloc)
			{
				insert(first, last);
			}

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _binary_tree() {}

			~map(){}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					clear();
					_alloc = x._alloc;
					_comp = x._comp;
					insert(x.begin(), x.end());
				}
				return (*this);
			}

			mapped_type& operator[] (const key_type& k)
			{
				node_ptr x = _binary_tree.search(k);

				if (x != _binary_tree.getNil())
					return (x->value.second);
				_binary_tree.insert(value_type(k, mapped_type()));
				x = _binary_tree.search(k);
				return (x->value.second);
			}

			allocator_type get_allocator(void) const
			{
				return (_alloc);
			}


			key_compare key_comp(void) const
			{
				return (_comp);
			}

			value_compare value_comp(void) const
			{
				return (value_compare(_comp));
			}

			bool empty(void) const
			{
				return (_binary_tree.size() == 0);
			}

			size_type size(void) const
			{
				return (_binary_tree.size());
			}

			size_type max_size(void) const
			{
				return (_binary_tree.max_size());
			}

			const_iterator begin(void) const
			{
				return (const_iterator(_binary_tree.getRoot(), _binary_tree.getNil(), _binary_tree.min()));
			}

			iterator begin(void)
			{
				return (iterator(_binary_tree.getRoot(), _binary_tree.getNil(), _binary_tree.min()));
			}

			const_iterator end(void) const
			{
				return (const_iterator(_binary_tree.getRoot(), _binary_tree.getNil(), _binary_tree.getNil()));
			}

			iterator end(void)
			{
				return (iterator(_binary_tree.getRoot(), _binary_tree.getNil(), _binary_tree.getNil()));
			}

			const_reverse_iterator rbegin(void) const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rend(void) const
			{
				return (const_reverse_iterator(begin()));
			}

			reverse_iterator rend(void)
			{
				return (reverse_iterator(begin()));
			}

			iterator find(const key_type& k)
			{
				node_ptr x = _binary_tree.search(k);

				if (x == _binary_tree.getNil())
					return (end());
				return (iterator(_binary_tree.getRoot(), _binary_tree.getNil(), x));
			}

			const_iterator find (const key_type& k) const
			{
				node_ptr x = _binary_tree.search(k);

				if (x == _binary_tree.getNil())
					return (end());
				return (const_iterator(_binary_tree.getRoot(), _binary_tree.getNil(), x));
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (insert(val).first);
			}

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				bool done = _binary_tree.insert(val);

				iterator it = find(val.first);
				return (ft::pair<iterator, bool>(it, done));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (InputIterator it = first; it != last; it++)
					insert(*(it));
			}

			void erase (iterator position)
			{
				erase((*position).first);
			}

			size_type erase(const key_type& k)
			{

				if (_binary_tree.delete_node(k))
					return (1);
				return (0);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
					erase((*(first++)).first);
			}

			void clear(void)
			{
				erase(begin(), end());
			}

			size_type count (const key_type& k) const
			{
				for (const_iterator it = begin(); it != end(); it++)
					if ((*(it)).first == k)
						return (1);
				return (0);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator it = begin();

				for (; it != end(); it++)
					if (_comp((*it).first, k) == false)
						break;
				return (it);
			}

			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = begin();

				for (; it != end(); it++)
					if (_comp((*it).first, k) == false)
						break;
				return (it);
			}

			iterator upper_bound (const key_type& k)
			{
				iterator it = begin();

				for (; it != end(); it++)
					if (_comp(k, (*it).first))
						break;
				return (it);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = begin();

				for (; it != end(); it++)
					if (_comp(k, (*it).first))
						break;
				return (it);
			}

			ft::pair<iterator, iterator> equal_range (const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			void swap (map& x)
			{
				_binary_tree.swap(x._binary_tree);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	class map<Key, T, Compare, Alloc>::value_compare
	{
		friend class map;

		protected:
			Compare _comp;
			value_compare (Compare c): _comp(c){}

		public:
			typedef bool			result_type;
			typedef value_type		first_argument_type;
			typedef value_type		second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return _comp(x.first, y.first);
			}
	};

	template <class T, class U>
	struct first_element : public std::unary_function<T, U>
	{
		const U& operator()(const T& elem) const
		{
			return elem.first;
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs == lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
}
