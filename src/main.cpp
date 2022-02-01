#include "test.hpp"

void printer(std::string title, std::string subtitle)
{
	std::cout << std::endl;
  std::cout  << title << ": " << subtitle << "\n" << std::endl;
}

void print_header(std::string container_name)
{
	std::string header = YELLOW + container_name + " TESTS:" +  + " press enter to continue\n";
	int width = 100 - (header.length() / 2);

	std::cout << '/' << std::setfill('*') << std::setw(100) << "/\n" << std::setfill(' ') << std::endl;
	std::cout << std::setw(width) << header << std::endl;
	std::cout << '/' << std::setfill('*') << std::setw(100) << "/\n" << std::setfill(' ') << std::endl;
}

int main()
{
	print_header("VECTOR");
	std::cout << std::endl;
	test_vector();
	print_header("STACK");
	test_stack();
	print_header("MAP");
	test_map();
	print_header("SET");
	test_set();

	return 0;
}
