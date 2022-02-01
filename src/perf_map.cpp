#if (1)
	# include "map.hpp"
#else
	# include <map>
	namespace ft = std;
#endif
#define COUNT 200000

int		main(void)
{
	ft::map<int, int>				map;
	ft::map<int, int>				cpy;
	ft::map<int, int>::iterator	it;

	for (int i = 0; i < COUNT; i++)
		map.insert(ft::make_pair(i, i));
	map.find(42);
	map.find(34);
	map.find(435);
	map.find(232);
	map.find(5756);
	map.find(904242);
	map.find(575645346);
	map.find(0);
	cpy = map;
	it = map.begin();
	for (int i = 0; i < COUNT / 2; i++)
		it++;
	map.erase(map.begin(), it);
	return (0);
}
