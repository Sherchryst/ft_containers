/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:53:00 by sgah              #+#    #+#             */
/*   Updated: 2022/02/01 14:38:46 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <functional>
# include <memory>
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

	template <class Key, class T, class KVal, class Compare = std::less<Key>, class Allocator = std::allocator<Node<T> > >
	class red_black_tree
	{
		public:
			typedef Key				key_type;
			typedef T				value_type;
			typedef Compare			compare_type;
			typedef Allocator		allocator_type;
			typedef std::size_t		size_type;

			typedef Node<value_type>		node_type;
			typedef Node<value_type>*	node_ptr;

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
				clear(_root);
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
					_root = y;
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
					_root = y;
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
				node_ptr x = _root;

				while (x != _nil)
				{
					y = x;
					if (_cmp(KVal()(node->value), KVal()(x->value)))
						x = x->left;
					else if (_cmp(KVal()(x->value), KVal()(node->value)))
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
					_root = node;
				else if (_cmp(KVal()(node->value), KVal()(y->value)))
					y->left = node;
				else
					y->right = node;
				_size++;
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

			node_ptr search(const key_type& key) const
			{
				return (search(_root, key));
			}

			node_ptr search(node_ptr x, const key_type& key) const
			{
				if (x == _nil)
					return _nil;
				else if (key == KVal()(x->value))
					return x;
				if (x != _nil)
				{
					if (_cmp(key, KVal()(x->value)))
						return search(x->left, key);
					return search(x->right, key);
				}
				return _nil;
			}

			void transplant(node_ptr x, node_ptr y)
			{
				if (x->parent == NULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->parent = x->parent;
			}

			/**------------------------------------------------------------------------
			 **                           delete_node
			 *?  Deleting a node may or may not disrupt the red-black properties
			 *?  if this action violates the red-black properties, then a fix it.
			 *! different case:
			 *! 1/ find the node to delete and save it position.
			 *! 2/ Save the color of z in origrinal_color.
			 *! 3/ If the left child of z is NULL
			 *!  a/ Assign the right child of z to x.
			 *!  b/ transplant z with x.
			 *! 4/ Else if the right child of z is NULL
			 *!  a/ Assign the left child of z into x.
			 *!  b/ transplant z with x
			 *! 5/ Else
			 *!  a/ Assign the minimum of right subtree of z into y.
			 *!  b/ Save the color of y in original_color.
			 *!  c/ Assign the rightChild of y into x.
			 *!  d/ If y is a child of z, then set the parent of x as y.
			 *!  e/ Else, transplant y with rightChild of y.
			 *!  f/ Transplant nodeToBeDeleted with y.
			 *!  g/ Set the color of y with originalColor.
			 *! 6/ If the originalColor is BLACK, call delete_fix(x).
			 *@param key key_type&
			 *@return bool
			 *------------------------------------------------------------------------**/
			bool delete_node(const key_type& key)
			{
				node_ptr x;
				node_ptr y;
				node_ptr z;

				z = search(key);
				if (z == _nil)
					return false;

				y = z;
				Color original_color = y->color;
				if (z->left == _nil)
				{
					x = z->right;
					transplant(z, z->right);
				}
				else if (z->right == _nil)
				{
					x = z->left;
					transplant(z, z->left);
				}
				else
				{
					y = min(z->right);
					original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				_alloc.destroy(z);
				_alloc.deallocate(z, 1);
				_size--;
				if (original_color == BLACK)
					delete_fix(x);
				return true;
			}

			/**========================================================================
			 **                           delete_fix
			 *?  fix red black tree because it violates the black depth property after deletion
			 *! different case:
			 *! 1/ Do the following until the x is not the root of the tree and the color of x is BLACK
			 *! 2/ If x is the left child of its parent then,
			 *!  a/ Assign w to the sibling of x.
			 *!  b/ If the sibling of x is RED,
			 *!   1- Set the color of the right child of the parent of x as BLACK.
			 *!   2- Set the color of the parent of x as RED.
			 *!   3- Left-Rotate the parent of x.
			 *!   4- Assign the rightChild of the parent of x to w.
			 *!  c/ If the color of both the right and the leftChild of w is BLACK,
			 *!   1- Set the color of w as RED
			 *!   2- Assign the parent of x to x.
			 *!  d/ Else if the color of the rightChild of w is BLACK
			 *!   1- Set the color of the leftChild of w as BLACK
			 *!   2- Set the color of w as RED
			 *!   3- Right-Rotate w.
			 *!   4- Assign the rightChild of the parent of x to w.
			 *!  e/ If any of the above cases do not occur, then do the following.
			 *!   1- Set the color of w as the color of the parent of x.
			 *!   2- Set the color of the parent of parent of x as BLACK.
			 *!   3- Set the color of the right child of w as BLACK.
			 *!   4- Left-Rotate the parent of x.
			 *!   5- Set x as the root of the tree.
			 *!  f/ Else same as above with right changed to left and vice versa.
			 *!  g/ Set the color of x as BLACK.
			 *@param x node_ptr
			 *@return type
			 *========================================================================**/
			void delete_fix(node_ptr x)
			{
				node_ptr w;

				while (x != _root && x->color == BLACK)
				{
					if (x == x->parent->left)
					{
						w = x->parent->right;
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							left_rotation(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w->right->color == BLACK)
							{
								w->left->color = BLACK;
								w->color = RED;
								right_rotation(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							left_rotation(x->parent);
							x = _root;
						}
					}
					else
					{
						w = x->parent->left;
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							right_rotation(x->parent);
							w = x->parent->left;
						}
						if (w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w->left->color == BLACK)
							{
								w->right->color = BLACK;
								w->color = RED;
								left_rotation(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							right_rotation(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK;
			}

			void clear(node_ptr const &x)
			{
				if (x == _nil)
					return ;
				clear(x->left);
				clear(x->right);
				_alloc.destroy(x);
				_alloc.deallocate(x, 1);
				_size--;
			}

			void swap (red_black_tree& x)
			{
				node_ptr tmp_root = _root;
				node_ptr tmp_nil = _nil;
				size_type tmp_size = _size;

				_root = x._root;
				x._root = tmp_root;
				_nil = x._nil;
				x._nil = tmp_nil;
				_size = x._size;
				x._size = tmp_size;
			}

			node_ptr getRoot(void) const
			{
				return (_root);
			}

			node_ptr getNil(void) const
			{
				return (_nil);
			}

			size_type size(void) const
			{
				return (_size);
			}

			size_type max_size(void) const
			{
				return (_alloc.max_size());
			}
	};
}
