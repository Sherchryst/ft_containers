/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:53:00 by sgah              #+#    #+#             */
/*   Updated: 2022/01/28 15:39:13 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <functional>
# include "node.hpp"

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (pred(*first1, *first2) == false)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
			first1++;
			first2++;
		}
		return ((first1 == last1) && (first2 != last2));
	}

	template <class K, class T, class KVal, class Compare = std::less<K>, class Allocator = std::allocator<Node<T> > >
	class red_black_tree
	{
		public:
			typedef K				key_type;
			typedef T				value_type;
			typedef Compare			compare_type;
			typedef Allocator		allocator_type;
			typedef std::size_t		size_type;

			typedef Node<value>		node_type;
			typedef Node<value>*	node_ptr;

		protected:
			allocator_type			_alloc;
			size_type				_size;
			compare_type			_cmp;
			node_ptr				_root;
			node_ptr				_nil;

		public:
			red_black_tree(const compare_type &cmp = compare_type(), const allocator_type &alloc = allocator_type()): _alloc(alloc), _size(0), _cmp(cmp)
			{
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, BLACK));
				_root = _nil;
			}

			~red_black_tree()
			{
				clear_red_black_tree(_root);
				_root = _nil;
				_alloc.destroy(_nil);
				_alloc.deallocate(_nil, 1);
			}

			/**==============================================
			 **              right_rotation
			 *?  In right rotation, we assume that the left child is not null.
			 *? -get the left child of x call it y
			 *? -y right child is now x left child
			 *? -x parent is now y parent
			 *? -check which side child was x,replace x by y
			 *? -x is now y right child
			 *@param x node_ptr
			 *@return void
			 *=============================================**/
			void right_rotation(node_ptr x)
			{
				node_ptr y = x->left;

				x->left = y->right;
				if (y->right != _nil)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			/**==============================================
			 **              left_rotation
			 *?  In left rotation, we assume that the right child is not null.
			 *? -get the right child of x call it y
			 *? -y left child is now x right child
			 *? -x parent is now y parent
			 *? -check which side child was x,replace x by y
			 *? - x is now y left child
			 *@param x node_ptr
			 *@return void
			 *=============================================**/
			void left_rotation(node_ptr x)
			{
				node_ptr y = x->right;

				x->right = y->left;
				if (y->left != _nil)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			/**========================================================================
			 **                           insert & fix insert
			 *?  We insert a new node to a red-black tree and call a function to fix violations
			 *? that could have occurred in the process of insertion.
			 *! Different case:
			 *! 1/ root is nil: the new node is inserted as root and colored black
			 *! 2/ the new node parent is black no fix to do
			 *! 3/ parent is red and uncle is red: grand parent become red, uncle become black, parent become black
			 *! 4/ parent is red, uncle is black, parent is a right child, the new node is a right child: Left rotation on grand parent, parent set to black and Sibling set to red
			 *! 5/ parent is red, uncle is black, parent is a right child, the new node is a left child: Right rotation on parent, Left rotation on grand parent, parent set to black and Sibling set to red
			 *! 6/ parent is red, uncle is black, parent is a left child, the new node is a left child: Right rotation on grand parent, parent set to black and Sibling set to red
			 *! 7/ parent is red, uncle is black, parent is a left child, the new node is a right child: Left rotation on parent, right rotation on grand parent, parent set to black and Sibling set to red
			 *@param value value_type
			 *@return bool
			 *========================================================================**/
			bool insert(const value_type& value)
			{
				node_ptr node;
				node = _alloc.allocate(1);
				_alloc.construct(node, node_type(value, NULL, _nil, _nil, RED));

				node_ptr y = NULL;
				node_ptr x = this->_root;

				while (x != _nil)
				{
					y = x;
					if (_comp(KeyOfValue()(node->value), KeyOfValue()(x->value)))
						x = x->left;
					else if (_comp(KeyOfValue()(x->value), KeyOfValue()(node->value)))
						x = x->right;
					else
					{
						_alloc.destroy(node);
						_alloc.deallocate(node, 1);
						return false;
					}
				}
				node->parent = y;
				if (y == NULL)
					this->_root = node;
				else if (_comp(KeyOfValue()(node->value), KeyOfValue()(y->value)))
					y->left = node;
				else
					y->right = node;
				this->_size++;
				if (node->parent == NULL)
				{
					node->color = BLACK;
					return true;
				}
				if (node->parent->parent == NULL)
					return true;
				fix_insert(node);
				return true;
			}

			void fix_insert(node_ptr x)
			{
				node_type *u;

				while (x->parent->color == RED)
				{
					if (x->parent == x->parent->parent->right)
						u = x->parent->parent->left;
					else
						u = x->parent->parent->right;
					if (u->color == RED)
					{
						u->color = BLACK;
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						x = x->parent->parent;
					}
					else if (x->parent == x->parent->parent->right)
					{
						if (x == x->parent->left)
						{
							x = x->parent;
							right_rotation(x);
						}
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						left_rotation(x->parent->parent);
					}
					else if (x->parent == x->parent->parent->left)
					{
						if (x == x->parent->right)
						{
							x = x->parent;
							left_rotation(x);
						}
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						right_rotation(x->parent->parent);
					}
					if (x == _root)
						break;
				}
				_root->color = BLACK;
			}
			/*============================ END OF INSERT & FIX ============================*/

			node_ptr min(void) const
			{
				node_ptr x = _root;
				if (_root == _nil)
					return _root;
				while (x->left != _nil)
					x = x->left;
				return x;
			}

			node_ptr max(void) const
			{
				node_ptr x = _root;
				if (_root == _nil)
					return _root;

				while (x->right != _nil)
					x = x->right;
				return x;
			}

			node_ptr min(node_ptr x) const
			{
				if (x == _nil)
					return _root;

				while (x->left != _nil)
					x = x->left;
				return x;
			}

			node_ptr max(node_ptr x) const
			{
				if (x == _nil)
					return _root;

				while (x->right != _nil)
					x = x->right;
				return x;
			}

			node_ptr successor(node_ptr x)
			{
				if (x->right != _nil)
					return min(x->right);
				node_ptr y = x->parent;
				while (y != _nil && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			node_ptr predecessor(node_ptr x)
			{
				if (x->left != _nil)
					return max(x->left);
				node_ptr y = x->parent;
				while (y != _nil && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}
	};
}
