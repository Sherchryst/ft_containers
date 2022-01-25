/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:41:56 by sgah              #+#    #+#             */
/*   Updated: 2022/01/25 04:18:17 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <cstddef>
# include "node.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};


/**========================================================================
 * *                                ITERATOR_TRAITS
 * ? Traits class defining properties of iterators.
 *========================================================================**/
	template <class Iter>
	class iterator_traits
	{
		public:
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
	};

/**========================================================================
 * *                                ITERATOR_TRAITS
 * !                             PARTIAL SPECIALIZATION
 * ? This type trait may be specialized for user-provided
 * ? types that may be used as iterators.
 *========================================================================**/
	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef ft::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef const T*							pointer;
			typedef const T&							reference;
			typedef ft::random_access_iterator_tag		iterator_category;
	};
/*============================ END OF ITERATOR_TRAITS =====================*/

/**========================================================================
 * *                                BIDIRECTIONAL_ITERATOR
 * ? Bidirectional iterators are iterators that can be used to access
 * ? the sequence of elements in a range in both directions.
 * * Can be compared for equivalence using the equality/inequality operators.
 * * Can be dereferenced as an rvalue.
 * * For non-constant iterators: Can be dereferenced as an lvalue.
 * * Can be incremented and decremented.
 *========================================================================**/
	template <class T, class N>
	class bidirectional_iterator
	{
		public:
			typedef N										node_type;
			typedef N*										node_ptr;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef const T*								const_pointer;
			typedef const T&								const_reference;
			typedef typename std::ptrdiff_t					difference_type;
			typedef typename ft::bidirectional_iterator_tag	iterator_category;

			operator bidirectional_iterator<value_type const, node_type const>() const
			{
				return (bidirectional_iterator<value_type const, node_type const>(_begin, _end, _ptr));
			}

			bidirectional_iterator& operator++()
			{
				if (_ptr != _end)
					_ptr = inheritor(_ptr);
				return *this;
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator ptr(*this);

				operator++();
				return (ptr);
			}

			bidirectional_iterator &operator--()
			{
				if (_ptr == _end)
					_ptr = max(_begin);
				else
					_ptr = precursor(_ptr);
				return (*this);
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator ptr(*this);

				operator--();
				return (ptr);
			}

			reference operator*()
			{
				return (this->_ptr->value);
			}

			const_reference operator*() const
			{
				return (this->_ptr->value);
			}

			pointer operator->()
			{
				return &(operator*());
			}

			const_pointer operator->() const
			{
				return &(operator*());
			}

			template<class Iterator, class Iter>
			friend bool operator==(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs);

			template<class Iterator, class Iter>
			friend bool operator!=(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs);

			bool operator==(const bidirectional_iterator& lhs) const
			{
				return (_ptr == lhs._ptr);
			}

			bool operator!=(const bidirectional_iterator& lhs) const
			{
				return (_ptr != lhs._ptr);
			}

		protected:
			node_ptr	_begin;
			node_ptr	_end;
			node_ptr	_ptr;

			node_ptr	min(node_ptr ptr)
			{
				while (ptr->left != _end)
					ptr = ptr->left;
				return (ptr);
			}

			node_ptr	max(node_ptr ptr)
			{
				while (ptr->right != _end)
					ptr = ptr->right;
				return (ptr);
			}

			node_ptr	inheritor(node_ptr ptr)
			{
				if (ptr->right != _end)
					return (min(ptr->right));

				node_ptr ptr_parent = ptr->parent;

				while (ptr_parent != NULL && ptr == ptr_parent->right)
				{
					ptr = ptr_parent;
					ptr_parent = ptr_parent->parent;
				}
				if (ptr_parent == NULL)
					return (_end);
				return (ptr_parent);
			}

			node_ptr	precursor(node_ptr ptr)
			{
				if (ptr->left != _end)
					return(maxi(ptr->left));

				node_ptr ptr_parent = ptr->parent;

				while (ptr_parent != _end && ptr == ptr_parent->left)
				{
					ptr = ptr_parent;
					ptr_parent = ptr_parent->parent;
				}
				return (ptr_parent);
			}
	};
	template<class Iterator, class Iter>
	bool operator==(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template<class Iterator, class Iter>
	bool operator!=(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}
/*============================ END OF BIDIRECTIONAL ITERATOR ==============*/

/**========================================================================
 * *                                RANDOM_ACCESS_ITERATOR
 * ? Random-access iterators are iterators that can be used to access
 * ? elements at an arbitrary offset position relative to the element
 * ? they point to, offering the same functionality as pointers.
 * * Can be compared for equivalence using the equality/inequality operators.
 * * Can be dereferenced as an rvalue.
 * * For non-constant iterators: Can be dereferenced as an lvalue.
 * * Can be incremented and decremented.
 * * Supports the arithmetic operators + and - between an iterator
 * * and an integer value subtracting an iterator from another.
 * * Can be compared with inequality relational operators (<, >, <= and >=).
 * * Supports compound assignment operations += and -=
 * * Supports the offset dereference operator ([])
 *========================================================================**/
	template <typename T>
	class random_access_iterator
	{
		public:
			typedef typename std::ptrdiff_t					difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef const T*								const_pointer;
			typedef const T&								const_reference;
			typedef typename ft::random_access_iterator_tag	iterator_category;

		protected
			pointer					_ptr;

		public:
			random_access_iterator(): _ptr(NULL){};
			random_access_iterator(pointer ptr): _ptr(ptr){}
			random_access_iterator(const random_access_iterator &rhs): _ptr(rhs._ptr){}
			virtual ~random_access_iterator(){}

			random_access_iterator	operator=(const random_access_iterator &rhs)
			{
				_ptr = rhs._ptr;
				return (*this);
			}

			operator				random_access_iterator<value_type const>(void) const
			{
				return (random_access_iterator<value_type const>(_ptr));
			}


	}

}
