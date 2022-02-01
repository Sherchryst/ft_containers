#include "test.hpp"

void print_vector(ft::vector<int> vector, std::string name)
{
	std::cout << name << ": ";
	for (ft::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void print_size(ft::vector<int> vector, std::string name)
{
	std::cout << name << " size: " << vector.size() << ", capacity: " << vector.capacity() << ", max_size: " << vector.max_size() << std::endl;
	std::cout << name << " empty() (1: true 0:false): " << vector.empty() << std::endl;
}

void test_vector()
{
  /********************************/
  /*		DEFAULT CONSTRUCTOR		*/
  /********************************/
	printer("DEFAULT CONSTRUCTOR", "ft::vector & std::vector");
	ft::vector<int> vector;
	print_size(vector, "vector");

	printer("FILL CONSTRUCTOR", "ft::vector & std::vector");
	ft::vector<int> vector_fill(10, 42);
	print_size(vector_fill, "vector_fill");
	print_vector(vector_fill, "vector_fill");

	printer("RANGE CONSTRUCTOR", "ft::vector & std::vector");
	ft::vector<int> vector_range(vector_fill.begin(), vector_fill.end());
	print_size(vector_range, "vector_range");
	print_vector(vector_range, "vector_range");

	printer("COPY CONSTRUCTOR (copy of range)", "ft::vector & std::vector");
	ft::vector<int> vector_copy(vector_range);
	print_size(vector_copy, "vector_copy");
	print_vector(vector_copy, "vector_copy");

	printer("ASSIGNATION OPERATOR", "ft::vector & std::vector");
	ft::vector<int> vector_assignation;
	vector_assignation = vector_copy;
	print_size(vector_assignation, "vector_assignation");
	print_vector(vector_assignation, "vector_assignation");

	vector = vector_assignation;


	printer("ITERATOR TEST");
	std::cout << "vector (iterator): ";
	for (ft::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;
	std::cout << "vector (const_iterator): ";
	for (ft::vector<int>::const_iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;
	std::cout << "vector (reverse_iterator): ";
	for (ft::vector<int>::reverse_iterator rit = vector.rbegin(); rit != vector.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl << std::endl;
	std::cout << "vector (const_reverse_iterator): ";
	for (ft::vector<int>::const_reverse_iterator rit = vector.rbegin(); rit != vector.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl << std::endl;


	printer("ACCESSOR AND MEMBER FUNCTIONS", "size, max_size, capacity, resize, empty, reserve");
	printer("BEFORE RESIZE");
	print_size(vector, "vector");

	printer("AFTER RESIZE(20)");
	vector.resize(20);
	print_size(vector, "vector");
	print_vector(vector, "vector");

	printer("AFTER RESIZE(20, 42)");
	vector.resize(40, 42);
	print_size(vector, "vector");
	print_vector(vector, "vector");


	printer("VECTOR EMPTY()");
	print_size(vector, "vector");


	printer("VECTOR RESERVE(max_size)");
	try
	{
		vector.reserve(vector.max_size());
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;


	printer("VECTOR RESERVE(max_size + 1)");
	try
	{
		vector.reserve(vector.max_size() + 1);
	}
	catch (std::exception &e)
	{
	std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;

	printer("VECTOR RESERVE(50)");
	vector.reserve(50);
	print_size(vector, "vector");
	print_vector(vector, "vector");

	printer("VECTOR [] OPERATOR");
	std::cout << "vector : ";
	for (int i = 0; vector[i]; i++)
		std::cout << vector[i] << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	printer("VECTOR AT()");
	try
	{
		std::cout << "vector : ";
		for (size_t i = 0; i < vector.size() + 1; i++)
			std::cout << vector.at(i) << " ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	printer("VECTOR FRONT()");
	std::cout << "vector : " << vector.front() << std::endl;
	std::cout << std::endl;

	printer("VECTOR BACK()");
	std::cout << "vector : " << vector.back() << std::endl;
	std::cout << std::endl;

	printer("VECTOR ASSIGN(first, last)");
	vector.assign(vector_fill.begin(), vector_fill.end());
	print_size(vector, "vector");
	print_vector(vector, "vector");

	printer("VECTOR ASSIGN(n, val)");
	vector.assign(10, 42);
	print_size(vector, "vector");
	print_vector(vector, "vector");

	printer("VECTOR PUSH_BACK(i * 42)");
	for (int i = 0; i <= 10; i++)
	{
		vector.push_back(i * 42);
		print_size(vector, "vector");
	}
	std::cout << std::endl;
	print_vector(vector, "vector");

	printer("VECTOR POP_BACK()");
	for (int i = 0; i < 10; i++)
	{
		vector.pop_back();
		print_size(vector, "vector");
	}
	std::cout << std::endl;
	print_vector(vector, "vector");

	printer("VECTOR INSERT(position, n, val)");
	vector.insert(vector.begin(), 5, 420);
	std::cout << "vector : ";
	print_vector(vector, "vector");

	printer("VECTOR INSERT(position, first, last)");
	vector.insert(vector.end(), vector_fill.begin(), vector_fill.end());
	print_vector(vector, "vector");

	printer("VECTOR ERASE(position)", "erasing first half");
	for (ft::vector<int>::iterator it = (vector.begin() + (vector.size() / 2)); it != vector.end() - 1 ; it++)
		vector.erase(it);
	print_vector(vector, "vector");

	printer("VECTOR SWAP() (MEMBER)", "swaping vector and range vector");
	printer("BEFORE SWAP");
	print_vector(vector, "vector");
	print_vector(vector_range, "vector_range");
	vector.swap(vector_range);
	printer("AFTER SWAP");
	print_vector(vector, "vector");
	print_vector(vector_range, "vector_range");

	printer("VECTOR SWAP() (NON MEMBER)", "swaping vector and range vector again");
	printer("BEFORE SWAP");
	print_vector(vector, "vector");
	print_vector(vector_range, "vector_range");
	ft::swap(vector, vector_range);
	printer("AFTER SWAP");
	print_vector(vector, "vector");
	print_vector(vector_range, "vector_range");


	printer("OPERATIONAL OPERATOR", "vector & vector_copy");
	print_vector(vector, "vector");
	print_vector(vector, "vector");
	std::cout << "vector == vector_copy: " << (vector == vector_copy) << std::endl;
	std::cout << "vector != vector_copy: " << (vector != vector_copy) << std::endl;
	std::cout << "vector < vector_copy: " << (vector < vector_copy) << std::endl;
	std::cout << "vector <= vector_copy: " << (vector <= vector_copy) << std::endl;
	std::cout << "vector > vector_copy: " << (vector > vector_copy) << std::endl;
	std::cout << "vector >= vector_copy: " << (vector >= vector_copy) << std::endl;
	std::cout << std::endl;

	printer("OPERATIONAL OPERATOR", "vector_assignation & vector_copy");
	print_vector(vector_assignation, "vector_assignation");
	print_vector(vector_copy, "vector_copy");
	std::cout << "vector_assignation == vector_copy: " << (vector_assignation == vector_copy) << std::endl;
	std::cout << "vector_assignation != vector_copy: " << (vector_assignation != vector_copy) << std::endl;
	std::cout << "vector_assignation < vector_copy: " << (vector_assignation < vector_copy) << std::endl;
	std::cout << "vector_assignation <= vector_copy: " << (vector_assignation <= vector_copy) << std::endl;
	std::cout << "vector_assignation > vector_copy: " << (vector_assignation > vector_copy) << std::endl;
	std::cout << "vector_assignation >= vector_copy: " << (vector_assignation >= vector_copy) << std::endl;

	std::cout << std::endl;

	printer("VECTOR CLEAR()");
	print_size(vector, "vector before clear()");
	print_size(vector_range, "vector_range before clear()");
	vector.clear();
	print_size(vector, "vector after(clear)");
	print_size(vector_range, "vector_range after(clear)");
}
