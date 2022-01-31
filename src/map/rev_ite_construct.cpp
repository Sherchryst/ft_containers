#include "test_map.hpp"

#define T1 int
#define T2 int

int		rev_ite_contruct(void)
{
	TESTED_NAMESPACE::map<T1, T2> mp;
	TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin();
	TESTED_NAMESPACE::map<T1, T2>::const_iterator cit = mp.begin();

	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator rit(it);

	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit(rit);
	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit_(it);
	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit_2(cit);

	std::cout << "OK" << std::endl;
	return (0);
}
