#include "test.hpp"

void test_stack()
{
	std::cout << "DEFAULT CONSTRUCTOR:" << "stack"<< std::endl;
	ft::stack<int> stack;

	std::cout << std::endl;

	std::cout << "SIZE:" << std::endl;
	std::cout << "stack size: " << stack.size() << std::endl;

	std::cout << std::endl;

	std::cout << "EMPTY:" << std::endl;
	std::cout << "stack empty() (1/true if empty 0/false if not): " << stack.empty() << std::endl;

	std::cout << std::endl;

	std::cout << "PUSH:" << std::endl;
	for (int i = 0; i <= 10; i++)
		stack.push(42 * i);

	std::cout << std::endl;

	std::cout << "SIZE:" << std::endl;
	std::cout << "stack size: " << stack.size() << std::endl;

	std::cout << std::endl;

	std::cout << "EMPTY:" << std::endl;
	std::cout << "stack empty() (1/true if empty 0/false if not): " << stack.empty() << std::endl;

	std::cout << std::endl;

	std::cout << "COPY CONSTRUCTOR:" << std::endl;
	ft::stack<int> stack_copy(stack);

	std::cout << std::endl;

	std::cout << "POP:" << std::endl;
	for (int i = 0; i <= 10; i++)
		stack.pop();

	std::cout << std::endl;

	std::cout << "ASSIGNATION OPERATOR:" << std::endl;
	stack_copy = stack;

	std::cout << std::endl;

	std::cout << "OPERATIONAL OPERATOR:" << std::endl;
	std::cout << "(stack == stack_copy) : " << (stack == stack_copy) << std::endl;
	std::cout << "(stack != stack_copy) : " << (stack != stack_copy) << std::endl;
	std::cout << "(stack < stack_copy) : " << (stack < stack_copy) << std::endl;
	std::cout << "(stack <= stack_copy) : " << (stack <= stack_copy) << std::endl;
	std::cout << "(stack > stack_copy) : " << (stack > stack_copy) << std::endl;
	std::cout << "(stack >= stack_copy) : " << (stack >= stack_copy) << std::endl;

	std::cout << std::endl;

	std::cout << std::endl;

}
