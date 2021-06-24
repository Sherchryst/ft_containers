/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:41:44 by sgah              #+#    #+#             */
/*   Updated: 2021/06/24 15:52:01 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR_H
# define LISTITERATOR_H

# include "Node.hpp"

namespace ft
{
	template <class T>
	class ListIterator {

		protected:
			pointer _ptr;

		public:

			typedef T value_type;
			typedef T& reference;
			typedef Node<T>* pointer;

			ListIterator(void);
			ListIterator();

			ListIterator(ListIterator const & src);
			~ListIterator(void);

			ListIterator &	operator=(const ListIterator &rhs);


		private:

	};
};

#endif
