/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:19:14 by sgah              #+#    #+#             */
/*   Updated: 2021/06/24 15:20:40 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <memory>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class List {

		public:

			List(void);

			List(List const & src);
			~List(void);

			List &	operator=(const List &rhs);


		private:

	};
};

#endif
