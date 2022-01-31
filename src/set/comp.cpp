#include "test_set.hpp"

#define T1 char
typedef TESTED_NAMESPACE::set<T1> _set;
typedef _set::const_iterator const_it;

static unsigned int i = 0;

void	ft_comp(const _set &st, const const_it &it1, const const_it &it2)
{
	bool res[2];

	std::cout << "\t-- [" << ++i << "] --" << std::endl;
	res[0] = st.key_comp()(*it1, *it2);
	res[1] = st.value_comp()(*it1, *it2);
	std::cout << "with [" << *it1 << " and " << *it2 << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

int		comp(void)
{
	_set	st;

	st.insert('a');
	st.insert('b');
	st.insert('c');
	st.insert('d');
	printSize(st);

	for (const_it it1 = st.begin(); it1 != st.end(); ++it1)
		for (const_it it2 = st.begin(); it2 != st.end(); ++it2)
			ft_comp(st, it1, it2);

	printSize(st);
	return (0);
}
