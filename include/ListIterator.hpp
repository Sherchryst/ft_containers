/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:41:44 by sgah              #+#    #+#             */
/*   Updated: 2021/06/24 21:34:27 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR_H
# define LISTITERATOR_H

# include "Node.hpp"

namespace ft
{
	template <class T>
	class ListIterator {
/**========================================================================
 **                          DEFINITION MEMBER TYPE
 *========================================================================**/
		public:
			typedef T value_type;
			typedef T& reference;
			typedef Node<T>* pointer;

/**========================================================================
 **                          NODE POINTER
 *========================================================================**/
		protected:
			pointer _ptr;

/**========================================================================
 **                          CONTRUCTOR DESTRUCTOR
 *========================================================================**/
		public:
			ListIterator(void){};

			ListIterator(pointer ptr): _ptr(ptr){};

			ListIterator(ListIterator const & src)
			{
				*this = src;
			};

			~ListIterator(void){};

/**========================================================================
 **                          OVERLOAD OPERATOR
 *========================================================================**/
			ListIterator &	operator=(const ListIterator &rhs)
			{
				_ptr = rhs._ptr;
				return (*this);
			}



	};
};

#endif
