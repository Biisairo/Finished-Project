#include "vector.hpp"
#include <vector>

#include "stack.hpp"
#include <stack>

#include <iostream>
#include <string>
#include <ctime>

int main()
{
// test stack
	std::cout << "\n====================\n     TEST STACK     \n====================\n\n";
	std::cout << "std::vecotr 을 받아서 만들어진 ft::stack 을 테스트 합니다" << std::endl;
	ft::stack<int, std::vector<int> > __v3;
	__v3.push(5);
	__v3.push(6);
	__v3.push(8);
	__v3.push(9);
	__v3.push(6);
	ft::stack<int, std::vector<int> > __v4 = __v3;
	ft::stack<int, std::vector<int> > __v5(__v3);
	std::cout << "\n원래의 스택======================" << std::endl;
	while (!(__v3.empty()))
	{
		std::cout << __v3.top() << std::endl;
		__v3.pop();
	}
	std::cout << "\n대입된 스택======================" << std::endl;
	while (!(__v4.empty()))
	{
		std::cout << __v4.top() << std::endl;
		__v4.pop();
	}
	std::cout << "\n복사된 스택======================" << std::endl;
	while (!(__v5.empty()))
	{
		std::cout << __v5.top() << std::endl;
		__v5.pop();
	}
}
