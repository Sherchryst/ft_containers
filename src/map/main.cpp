/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgah <sgah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:00:09 by sgah              #+#    #+#             */
/*   Updated: 2022/01/31 16:27:43 by sgah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_map.hpp>
#include <iostream>
#include <wchar.h>

int main()
{
	std::cout << "/*================================ BOUNDS ==============================*/" << std::endl;
	bounds();
	getwchar();
	std::cout << "/*================================ COMP ==============================*/" << std::endl;
	comp();
	getwchar();
	std::cout << "/*================================ COPY_CONSTRUCT ==============================*/" << std::endl;
	copy_construct();
	getwchar();
	std::cout << "/*================================ EMPTY ==============================*/" << std::endl;
	empty();
	getwchar();
	std::cout << "/*================================ ERASE ==============================*/" << std::endl;
	erase();
	getwchar();
	erase2();
	getwchar();
	std::cout << "/*================================ COUNT ==============================*/" << std::endl;
	find_count();
	getwchar();
	std::cout << "/*================================ INSERT ==============================*/" << std::endl;
	insert();
	getwchar();
	insert2();
	getwchar();
	std::cout << "/*================================ ITER ==============================*/" << std::endl;
	ite_arrow();
	getwchar();
	std::cout << "/*================================ BASICS ==============================*/" << std::endl;
	more();
	getwchar();
	std::cout << "/*================================ OPERATOR[] ==============================*/" << std::endl;
	op_sqbr();
	getwchar();
	std::cout << "/*================================ OPERATORS ==============================*/" << std::endl;
	relational_ope();
	getwchar();
	std::cout << "/*================================ REVERSE ITER CONSTRUCT ==============================*/" << std::endl;
	rev_ite_contruct();
	getwchar();
	std::cout << "/*================================ REVERSE ITER ==============================*/" << std::endl;
	rite_arrow();
	getwchar();
	rite();
	getwchar();
	std::cout << "/*================================ SWAP ==============================*/" << std::endl;
	swap ();
	getwchar();
	std::cout << "/*================================ HARD TEST CONSTRUCT ==============================*/" << std::endl;
	tricky_construct();
	getwchar();
	std::cout << "/*================================ HARD TEST ERASE ==============================*/" << std::endl;
	tricky_erase();
}
