/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 02:38:28 by sgah              #+#    #+#             */
/*   Updated: 2022/01/26 14:28:37 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	enum Color
	{
		BLACK,
		RED
	};

/**========================================================================
 **                           STRUCT NODE
 *?  struct used in red black tree class and also bidirectional iterator
 *========================================================================**/
	template <class T>
	struct Node
	{
		typedef	T	value_type;

		value_type	value;

		struct Node	*parent;
		struct Node	*left;
		struct Node	*right;

		Color		color;

		Node(value_type value, Node* parent, Node* left, Node* right, Color color): value(value), parent(parent), left(left), right(right), color(color) {}
	};
}
