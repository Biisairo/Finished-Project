#include "set.hpp"
#include "map.hpp"
#include <set>

#include <iostream>
#include <string>
#include <ctime>

class A
{
	public:
		int* a;
		A()
		{
			// std::cout << "==============constructor\n";
			// std::cout << "new : " << this << std::endl;
			a = new int(1);
		}
		~A()
		{
			// std::cout << "==============destructor\n";
			// std::cout << "kil : " << this << std::endl;
			delete a;
		}
		A(const A& a)
		{
			// std::cout << "=================copy\n";
			// std::cout << "ori : " << &a << std::endl;
			// std::cout << "dst : " << this << std::endl;
			int tmp = *(a.a);
			this->a = new int(tmp);
		}
};

bool operator==(const A& j, const A& k)
	{return *(j.a) == *(k.a);}
bool operator!=(const A& j, const A& k)
	{return !(j == k);}
bool operator>(const A& j, const A& k)
	{return *(j.a) > *(k.a);}
bool operator<(const A& j, const A& k)
	{return *(j.a) < *(k.a);}
bool operator>=(const A& j, const A& k)
	{return *(j.a) >= *(k.a);}
bool operator<=(const A& j, const A& k)
	{return *(j.a) <= *(k.a);}

void leak_test()
{
	ft::set<A> leak;
	A a;
	A b;
	A c;
	A d;
	A e;
	leak.insert(a);
	leak.insert(b);
	leak.insert(c);
	leak.insert(d);
	leak.insert(e);
	leak.erase(a);
	leak.erase(b);
	leak.clear();
	leak.erase(c);
	leak.erase(d);
	leak.erase(e);
}

int main()
{
// test map
	std::cout << "\n====================\n      TEST SET      \n====================\n\n";
	std::cout << "ft============================\n";
	ft::set<int> m;
	m.insert(1);
	m.insert(2);
	m.insert(3);
	m.insert(4);
	m.insert(5);
	ft::set<int>::iterator it = m.begin();
	while (it != m.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "swap===========================\n";
	ft::set<int> m2;
	m2.insert(10);
	m2.insert(11);
	m2.insert(12);
	m.swap(m2);
	it = m.begin();
	while (it != m.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
	it = m2.begin();
	while (it != m2.end())
	{
		std::cout << *it << std::endl;
		it++;
	}

	////////////////
	std::cout << std::endl;
	///////////////

	std::cout << "std============================\n";
	std::set<int> m3;
	m3.insert(1);
	m3.insert(2);
	m3.insert(3);
	m3.insert(4);
	m3.insert(5);
	std::set<int>::iterator it3 = m3.begin();
	while (it3 != m3.end())
	{
		std::cout << *it3 << std::endl;
		it3++;
	}
	std::cout << "swap============================\n";
	std::set<int> m4;
	m4.insert(10);
	m4.insert(11);
	m4.insert(12);
	m3.swap(m4);
	it3 = m3.begin();
	while (it3 != m3.end())
	{
		std::cout << *it3 << std::endl;
		it3++;
	}
	it3 = m4.begin();
	while (it3 != m4.end())
	{
		std::cout << *it3 << std::endl;
		it3++;
	}

// test dup
	std::cout << "\n====================\n    TEST MAP DUP    \n====================\n\n";
	ft::set<int> set_int;
	for (int i = 0; i < INT_MAX / 10000; ++i)
		set_int.insert(rand());
	int sum = 0;
	for (int i = 0; i < INT_MAX / 1000; i++)
	{
		int access = rand();
		if (set_int.count(access) != 0 && set_int.count(access) != 1)
			sum++;
	}
	std::cout << "중복된 횟수 : " << sum << std::endl << std::endl;

// leak test
	std::cout << "\n====================\n     TEST LEAK      \n====================\n\n";
	leak_test();
	system("leaks container");
}
