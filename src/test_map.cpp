#include "test.hpp"


void print_map(ft::map<char, int> map, std::string name)
{
	std::cout << name << ":\n";
	for (ft::map<char, int>::iterator it = map.begin(); it != map.end(); it++)
		std::cout << (*it).first << " = " << (*it).second << ", ";
	std::cout << std::endl << std::endl;
}

void print_size(ft::map<char, int> map, std::string name)
{
	std::cout << name << " size: " << map.size() << ", max_size: " << map.max_size() << std::endl;
	std::cout << name << " empty() (1: true 0:false): " << map.empty() << std::endl;
	std::cout << std::endl;
}

void test_map()
{
	printer("CONSTRUCTOR", "ft::map & std::map");
	ft::map<char, int> map;
	print_size(map, "map");

	char c = 'a';
	for (int i = 1; i <= 13; i++, c++)
	{
		map[c] = i;
	}
	print_map(map, "map");
	print_size(map, "map");

	printer("RANGE", "ft::map & std::map");
	ft::map<char, int> map_range(map.begin(), map.end());
	print_size(map_range, "map_range");
	print_map(map_range, "map_range");

	printer("COPY CONSTRUCTOR (copy of range)", "ft::map & std::map");
	ft::map<char, int> map_copy(map_range);
	print_size(map_copy, "map_copy");
	print_map(map_copy, "map_copy");


	printer("ASSIGNATION OPERATOR", "ft::map & std::map");
	ft::map<char, int> map_assignation;
	map_assignation = map_copy;
	print_size(map_assignation, "map_assignation");
	print_map(map_assignation, "map_assignation");


	printer("ITERATORS TESTS");
	std::cout << "map (iterator): ";
	for (ft::map<char, int>::iterator it = map.begin(); it != map.end(); it++)
		std::cout << (*it).first << " = " << (*it).second << ", ";
	std::cout << std::endl << std::endl;
	std::cout << "map (const_iterator): ";
	for (ft::map<char, int>::const_iterator it = map.begin(); it != map.end(); it++)
		std::cout << (*it).first << " = " << (*it).second << ", ";
	std::cout << std::endl << std::endl;
	std::cout << "map (reverse_iterator): ";
	for (ft::map<char, int>::reverse_iterator rit = map.rbegin(); rit != map.rend(); rit++)
		std::cout << (*rit).first << " = " << (*rit).second << ", ";
	std::cout << std::endl << std::endl;
	std::cout << "map (const_reverse_iterator): ";
	for (ft::map<char, int>::const_reverse_iterator rit = map.rbegin(); rit != map.rend(); rit++)
		std::cout << (*rit).first << " = " << (*rit).second << ", ";
	std::cout << std::endl << std::endl;

	printer("ACCESSOR AND MEMBER FUNCTIONS", "size, max_size, empty");
	print_size(map, "map");

	printer("MAP INSERT(val)");
	for (int i = 14; i <= 19; i++, c++)
		map.insert(ft::make_pair(c, i));
	print_map(map, "map");
	print_size(map, "map");

	printer("MAP INSERT(position, val)");
	for (int i = 20; i <= 26; i++, c++)
		map.insert(ft::make_pair(c, i));

	print_map(map, "map");
	print_size(map, "map");

	printer("MAP INSERT(first, last)", "map -> map_copy");
	printer("BEFORE INSERT");
	print_map(map_copy, "map_copy");

	printer("AFTER INSERT");
	map_copy.insert(map.begin(), map.end());
	print_map(map_copy, "map_copy");
	print_size(map_copy, "map_copy");

	printer("MAP ERASE(position)", "erasing first half of map_copy");
	ft::map<char, int>::iterator ft_it_half = map_copy.find('n');
	for (ft::map<char, int>::iterator it = map_copy.begin(); it != ft_it_half; it++)
		map_copy.erase(it);
	print_map(map_copy, "map_copy");
	print_size(map_copy, "map_copy");

	printer("MAP ERASE(key)", "erasing another half of map_copy");
	c = 'n';
	for (int i = 0; i < 6; i++, c++)
		map_copy.erase(c);

	print_map(map_copy, "map_copy");
	print_size(map_copy, "map_copy");

	printer("MAP ERASE(first, last)", "finishing the job map_copy");
	map_copy.erase(map_copy.begin(), map_copy.end());
	print_map(map_copy, "map_copy");
	print_size(map_copy, "map_copy");

	printer("MAP SWAP() (MEMBER)", "swaping map_range and map_copy");
	printer("BEFORE SWAP");
	print_map(map_range, "map_range");
	print_map(map_copy, "map_copy");
	map_range.swap(map_copy);
	printer("AFTER SWAP");
	print_map(map_range, "map_range");
	print_map(map_copy, "map_copy");

	printer("MAP CLEAR", "clearing map copy again");
	printer("BEFORE");
	print_map(map_copy, "map_copy");
	print_size(map_copy, "map_copy");
	map_copy.clear();
	printer("AFTER");
	print_map(map_copy, "map_copy");
	print_size(map_copy, "map_copy");

	printer("MAP FIND(key) const and non_const");
	ft::map<char, int>::iterator find_a = map.find('a');
	ft::map<char, int>::const_iterator find_z = map.find('z');
	std::cout << "find('a'): " << (*find_a).first << " = " << (*find_a).second << '\n';
	std::cout << "find('z'): " << (*find_z).first << " = " << (*find_z).second << '\n';

	printer("MAP COUNT(key)");
	std::cout << 'a';
	if (map.count('a') > 0)
		std::cout << " is an element of map.\n";
	else
		std::cout << " is not an element of map.\n";
	std::cout << '1';
	if (map.count('1') > 0)
		std::cout << " is an element of map.\n";
	else
		std::cout << " is not an element of map.\n";

	printer("MAP LOWER_BOUND AND UPPER_BOUND", "using it to erase from b to g");
	ft::map<char,int>::iterator itlow = map.lower_bound('b');
	ft::map<char,int>::iterator itup = map.upper_bound('g');
	map.erase(itlow, itup);
	print_map(map, "map");
	print_size(map, "map");

	printer("MAP EQUAL_RANGE", "for h");
	ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
	ret = map.equal_range('h');
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	printer("MAP KEY_COMP AND VALUE_COMP", "display everything lower than m");
	ft::map<char,int>::key_compare mycomp = map.key_comp();

	char highest_key = 'm';
	ft::pair<char,int> highest = *map.find('m');

	ft::map<char,int>::iterator it = map.begin();
	while (map.value_comp()(*it, highest) \
		&& mycomp((*it).first, highest_key))
	{
		std::cout << it->first << " => " << it->second << '\n';
		it++;
	}
}
