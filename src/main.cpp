#include "test.hpp"

void printer(std::string title, std::string subtitle)
{
	std::cout << std::endl;
  std::cout  << title << ": " << subtitle << "\n" << std::endl;
}

int main()
{
	std::cout << "/*================================ VECTOR ==============================*/" << std::endl;
	test_vector();
	std::cout << "/*================================ STACK ==============================*/" << std::endl;
	test_stack();
	std::cout << "/*================================ MAP ==============================*/" << std::endl;
	test_map();
	std::cout << "/*================================ SET ==============================*/" << std::endl;
	test_set();

	return 0;
}
