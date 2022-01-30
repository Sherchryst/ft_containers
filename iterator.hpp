/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:41:56 by sgah              #+#    #+#             */
/*   Updated: 2022/01/29 16:06:20 by sgah             ###   ########.fr       */
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
			typedef node_type*								node_ptr;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef const T*								const_pointer;
			typedef const T&								const_reference;
			typedef typename std::ptrdiff_t					difference_type;
			typedef typename ft::bidirectional_iterator_tag	iterator_category;

			bidirectional_iterator(): _begin(NULL), _end(NULL), _ptr(NULL) {}

			bidirectional_iterator(node_ptr root, node_ptr nil, node_ptr ptr): _begin(root), _end(nil), _ptr(ptr) {}

			bidirectional_iterator(const bidirectional_iterator &src):_begin(src._begin), _end(src._end), _ptr(src._ptr) {}

			virtual ~bidirectional_iterator() {}

			operator				bidirectional_iterator<value_type const, node_type const>() const
			{
				return (bidirectional_iterator<value_type const, node_type const>(_begin, _end, _ptr));
			}

			bidirectional_iterator&	operator++(void)
			{
				if (_ptr != _end)
					_ptr = inheritor(_ptr);
				return *this;
			}

			bidirectional_iterator	operator++(int)
			{
				bidirectional_iterator ptr(*this);

				operator++();
				return (ptr);
			}

			bidirectional_iterator&	operator--(void)
			{
				if (_ptr == _end)
					_ptr = max(_begin);
				else
					_ptr = precursor(_ptr);
				return (*this);
			}

			bidirectional_iterator	operator--(int)
			{
				bidirectional_iterator ptr(*this);

				operator--();
				return (ptr);
			}

			reference				operator*(void)
			{
				return (this->_ptr->value);
			}

			const_reference			operator*(void) const
			{
				return (this->_ptr->value);
			}

			pointer					operator->(void)
			{
				return &(operator*());
			}

			const_pointer			operator->(void) const
			{
				return &(operator*());
			}

			template<class Iterator, class Iter>
			friend bool operator==(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs);

			template<class Iterator, class Iter>
			friend bool operator!=(ft::bidirectional_iterator<Iterator, ft::Node<Iterator> > const &lhs, ft::bidirectional_iterator<Iter, ft::Node<Iter> > const &rhs);

			bool					operator==(const bidirectional_iterator& lhs) const
			{
				return (_ptr == lhs._ptr);
			}

			bool					operator!=(const bidirectional_iterator& lhs) const
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
					return(max(ptr->left));

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

		protected:
			pointer	_ptr;

		public:
			random_access_iterator(void): _ptr(NULL){};

			random_access_iterator(pointer ptr): _ptr(ptr){}

			random_access_iterator(const random_access_iterator &rhs): _ptr(rhs._ptr){}

			virtual ~random_access_iterator(void){}

			operator				random_access_iterator<value_type const>(void) const
			{
				return (random_access_iterator<value_type const>(_ptr));
			}

			random_access_iterator&	operator++(void)
			{
				++_ptr;
				return (*this);
			}

			random_access_iterator	operator++(int)
			{
				random_access_iterator ptr(*this);

				++_ptr;
				return (ptr);
			}

			random_access_iterator&	operator--(void)
			{
				--_ptr; return *this;
			}

			random_access_iterator	operator--(int)
			{
				random_access_iterator ptr(*this);

				--_ptr;
				return (ptr);
			}

			random_access_iterator	operator+(difference_type diff) const
			{
				return (random_access_iterator<T>(_ptr + diff));
			}

			random_access_iterator	operator-(difference_type diff) const
			{
				return (random_access_iterator<T>(_ptr - diff));
			}

			difference_type			operator-(random_access_iterator const &src) const
			{
				return (_ptr - src._ptr);
			}

			random_access_iterator&	operator+=(difference_type diff)
			{
				_ptr += diff;
				return (*this);
			}
			random_access_iterator&	operator-=(difference_type diff)
			{
				_ptr -= diff;
				return (*this);
			}

			reference				operator*(void)
			{
				return (*_ptr);
			}

			pointer					operator->(void)
			{
				return (_ptr);
			}

			reference				operator[](const difference_type diff) const
			{
				return (_ptr[diff]);
			}

			random_access_iterator	operator=(const random_access_iterator &rhs)
			{
				_ptr = rhs._ptr;
				return (*this);
			}

			bool					operator==(const random_access_iterator&	src) const
			{
				return (_ptr == src._ptr);
			}

			bool					operator!=(const random_access_iterator&	src) const
			{
				return (_ptr != src._ptr);
			}

			bool					operator<(const random_access_iterator&	src) const
			{
				return (_ptr < src._ptr);
			}

			bool					operator<=(const random_access_iterator&	src) const
			{
				return (_ptr <= src._ptr);
			}

			bool					operator>(const random_access_iterator&	src) const
			{
				return (_ptr > src._ptr);
			}

			bool					operator>=(const random_access_iterator&	src) const
			{
				return (_ptr >= src._ptr);
			}

			template <class Iterator_lhs, class Iterator_rhs>
			friend bool operator==(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs);

			template <class Iterator_lhs, class Iterator_rhs>
			friend bool operator!=(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs);

			template <class Iterator_lhs, class Iterator_rhs>
			friend bool operator<(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs);

			template <class Iterator_lhs, class Iterator_rhs>
			friend bool operator<=(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs);

			template <class Iterator_lhs, class Iterator_rhs>
			friend bool operator>(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs);

			template <class Iterator_lhs, class Iterator_rhs>
			friend bool operator>=(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs);

	};

	template <class Iterator_lhs, class Iterator_rhs>
	bool operator==(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template <class Iterator_lhs, class Iterator_rhs>
	bool operator!=(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}

	template <class Iterator_lhs, class Iterator_rhs>
	bool operator<(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs)
	{
		return (lhs._ptr < rhs._ptr);
	}

	template <class Iterator_lhs, class Iterator_rhs>
	bool operator<=(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs)
	{
		return (lhs._ptr <= rhs._ptr);
	}

	template <class Iterator_lhs, class Iterator_rhs>
	bool operator>(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs)
	{
		return (lhs._ptr > rhs._ptr);
	}

	template <class Iterator_lhs, class Iterator_rhs>
	bool operator>=(const random_access_iterator<Iterator_lhs>& lhs, const random_access_iterator<Iterator_rhs>& rhs)
	{
		return (lhs._ptr >= rhs._ptr);
	}

	template<class T>
	ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n, ft::random_access_iterator<T> const& rhs)
	{
		return (rhs + n);
	}
/*============================ END OF RANDOM_ACCESS_ITERATOR ============================*/

/**========================================================================
 * *                                REVERSE_ITERATOR
 * ? ft::reverse_iterator produces a new iterator that moves from
 * ? the end to the beginning of the sequence defined by the underlying
 * ? bidirectional iterator.
 *========================================================================**/
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

		protected:
			iterator_type	_ptr;

		public:
			reverse_iterator(void): _ptr(iterator_type()){};

			explicit reverse_iterator(iterator_type _ptr): _ptr(_ptr){};

			template <class Iter>
			reverse_iterator(reverse_iterator<Iter> const& rev_it): _ptr(rev_it.base()) {};

			virtual ~reverse_iterator(void){}

			iterator_type		base(void) const
			{
				return (_ptr);
			}

			reference			operator*(void) const
			{
				iterator_type ptr(_ptr);
				return (*--ptr);
			}

			pointer				operator->(void) const
			{
				return &(operator*());
			}

			reference			operator[](difference_type diff) const
			{
				return *(*this + diff);
			}

			reverse_iterator&	operator=(reverse_iterator const& rhs)
			{
				_ptr = rhs._ptr;
				return *this;
			}

			reverse_iterator&	operator++(void)
			{
				--_ptr;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator<iterator_type> iter(*this);

				--_ptr;
				return (iter);
			}

			reverse_iterator&	operator--(void)
			{
				++_ptr;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator<iterator_type> iter(*this);

				++_ptr;
				return (iter);
			}

			reverse_iterator	operator+(difference_type diff) const
			{
				return (reverse_iterator<iterator_type>(_ptr - diff));
			}

			reverse_iterator	operator-(difference_type diff) const
			{
				return (reverse_iterator<iterator_type>(_ptr + diff));
			}

			difference_type		operator+(const Iterator &src) const
			{
				return (_ptr - src._ptr);
			}

			difference_type		operator-(const Iterator &src) const
			{
				return (_ptr + src._ptr);
			}

			reverse_iterator&	operator+= (difference_type diff)
			{
				_ptr -= diff;
				return (*this);
			}

			reverse_iterator&	operator-=(difference_type diff)
			{
				_ptr += diff;
				return (*this);
			}

			difference_type		substract(const reverse_iterator<Iterator> rhs) const
			{
				return (rhs.base() - this->_ptr);
			}
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	/* NON MEMBER OPERATION CONST AND NON CONST */
	template <class Iterator, class Iter>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator!= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.substract(rhs));
	}

	template <class Iterator, class Iter>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.substract(rhs));
	}

	template <class Iterator, class Iter>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iter> &rev_it)
	{
		return (rev_it + n);
	}
/*============================ END OF REVERSE_ITERATOR ============================*/
}
