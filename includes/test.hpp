#pragma once

#if(TEST_FT)
	#include "vector.hpp"
	#include "set.hpp"
	#include "stack.hpp"
	#include "map.hpp"
#else
	#include <set>
	#include <map>
	#include <vector>
	#include <stack>
	namespace ft = std;
#endif

#include <string>
#include <iostream>
#include <iomanip>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define SET "\033[0m"

void printer(std::string title, std::string subtitle = "");
void test_vector();
void test_stack();
void test_map();
void test_set();

