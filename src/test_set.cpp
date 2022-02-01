#include "test.hpp"

void print_set(ft::set<char> set, std::string name)
{
	std::cout << name << ":\n";
	for (ft::set<char>::iterator it = set.begin(); it != set.end(); it++)
		std::cout << *it << ", ";
	std::cout << std::endl;
	std::cout << std::endl;
}

void print_size(ft::set<char> set, std::string name)
{
	std::cout << name << " size: " << set.size() << ", max_size: " << set.max_size() << std::endl;
	std::cout << name << " empty() (1: true 0:false): " << set.empty() << std::endl;
	std::cout << std::endl;
}

void test_set()
{
	printer("CONSTRUCTOR", "set");
	ft::set<char> set;
	print_size(set, "set");

	char c = 'a';
	for (int i = 1; i <= 13; i++, c++)
	set.insert(c);

	print_set(set, "set");
	print_size(set, "set");

	printer("RANGE", "set");
	ft::set<char> set_range(set.begin(), set.end());
	print_size(set_range, "set_range");
	print_set(set_range, "set_range");

	printer("COPY CONSTRUCTOR (copy of range)", "set");
	ft::set<char> set_copy(set_range);
	print_size(set_copy, "set_copy");
	print_set(set_copy, "set_copy");


	printer("ASSIGNATION OPERATOR", "set");
	ft::set<char> set_assignation;
	set_assignation = set_copy;
	print_size(set_assignation, "set_assignation");
	print_set(set_assignation, "set_assignation");


	printer("ITERATORS TESTS");
	std::cout << "set (iterator): ";
	for (ft::set<char>::iterator it = set.begin(); it != set.end(); it++)
		std::cout << *it << ", ";
	std::cout << std::endl << std::endl;
	std::cout << "set (const_iterator): ";
	for (ft::set<char>::const_iterator it = set.begin(); it != set.end(); it++)
		std::cout << *it << ", ";
	std::cout << std::endl << std::endl;
	std::cout << "set (reverse_iterator): ";
	for (ft::set<char>::reverse_iterator rit = set.rbegin(); rit != set.rend(); rit++)
		std::cout << *rit << ", ";
	std::cout << std::endl << std::endl;
	std::cout << "set (const_reverse_iterator): ";
	for (ft::set<char>::const_reverse_iterator rit = set.rbegin(); rit != set.rend(); rit++)
		std::cout << *rit << ", ";
	std::cout << std::endl << std::endl;

	printer("ACCESSOR AND MEMBER FUNCTIONS", "size, max_size, empty");
	print_size(set, "set");

	printer("SET INSERT(val)");
	for (int i = 14; i <= 19; i++, c++)
	{
		set.insert(c);
	}
	print_set(set, "set");
	print_size(set, "set");

	printer("SET INSERT(position, val)");
	for (int i = 20; i <= 26; i++, c++)
	{
		set.insert(c);
	}
	print_set(set, "set");
	print_size(set, "set");

	printer("SET INSERT(first, last)", "set -> set_copy");
	printer("BEFORE INSERT");
	print_set(set_copy, "set_copy");

	printer("AFTER INSERT");
	set_copy.insert(set.begin(), set.end());
	print_set(set_copy, "set_copy");
	print_size(set_copy, "set_copy");

	printer("SET ERASE(position)", "erasing first half of set_copy");
	ft::set<char>::iterator ft_it_half = set_copy.find('n');
	for (ft::set<char>::iterator it = set_copy.begin(); it != ft_it_half; it++)
		set_copy.erase(it);
	print_set(set_copy, "set_copy");
	print_size(set_copy, "set_copy");

	printer("SET ERASE(key)", "erasing another half of set_copy");
	c = 'n';
	for (int i = 0; i < 6; i++, c++)
	{
		set_copy.erase(c);
	}
	print_set(set_copy, "set_copy");
	print_size(set_copy, "set_copy");

	printer("SET ERASE(first, last)", "finishing the job set_copy");
	set_copy.erase(set_copy.begin(), set_copy.end());
	print_set(set_copy, "set_copy");
	print_size(set_copy, "set_copy");

	printer("SET SWAP() (MEMBER)", "swaping set_range and set_copy");
	printer("BEFORE SWAP");
	print_set(set_range, "set_range");
	print_set(set_copy, "set_copy");
	set_range.swap(set_copy);
	printer("AFTER SWAP");
	print_set(set_range, "set_range");
	print_set(set_copy, "set_copy");

	printer("SET CLEAR", "clearing set copy again");
	printer("BEFORE");
	print_set(set_copy, "set_copy");
	print_size(set_copy, "set_copy");
	set_copy.clear();
	printer("AFTER");
	print_set(set_copy, "set_copy");
	print_size(set_copy, "set_copy");

	printer("SET FIND(key) const and non_const");
	ft::set<char>::iterator find_a = set.find('a');
	ft::set<char>::const_iterator find_z = set.find('z');
	std::cout << "find('a'): " << *find_a << '\n';
	std::cout << "find('z'): " << *find_z << '\n';

	printer("SET COUNT(key)");
	std::cout << 'a';
	if (set.count('a') > 0)
		std::cout << " is an element of set.\n";
	else
		std::cout << " is not an element of set.\n";
	std::cout << '1';
	if (set.count('1') > 0)
		std::cout << " is an element of set.\n";
	else
		std::cout << " is not an element of set.\n";

	printer("SET LOWER_BOUND AND UPPER_BOUND", "using it to erase from b to g");
	ft::set<char,int>::iterator itlow = set.lower_bound('b');
	ft::set<char,int>::iterator itup = set.upper_bound('g');
	set.erase(itlow, itup);
	print_set(set, "set");
	print_size(set, "set");

	printer("SET EQUAL_RANGE", "for h");
	ft::pair<ft::set<char,int>::iterator,ft::set<char,int>::iterator> ret;
	ret = set.equal_range('h');
	std::cout << "lower bound points to: ";
	std::cout << *(ret.first) << '\n';
	std::cout << "upper bound points to: ";
	std::cout << *(ret.second) << '\n';

	printer("SET KEY_COMP AND VALUE_COMP", "display everything lower than m");
	ft::set<char>::key_compare mycomp = set.key_comp();

	char highest_key = 'm';
	char highest = *set.find('m');

	ft::set<char,int>::iterator it = set.begin();
	while (set.value_comp()(*it, highest) \
		&& mycomp((*it), highest_key))
	{
		std::cout << *it << " => " << *it << '\n';
		it++;
	}
}
