#include "map.hpp"
#include <map>

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

void leak_test()
{
	ft::map<int, A> leak;
	leak.insert(ft::make_pair(2, A()));
	leak.insert(ft::make_pair(5, A()));
	leak.insert(ft::make_pair(1, A()));
	leak.insert(ft::make_pair(4, A()));
	leak.insert(ft::make_pair(3, A()));
	leak.erase(1);
	leak.erase(2);
	leak.clear();
	leak.erase(3);
	leak.erase(4);
	leak.erase(5);
}

int main()
{
// test map
	std::cout << "\n====================\n      TEST MAP      \n====================\n\n";
	std::cout << "ft============================\n";
	ft::pair<ft::map<int, std::string>::iterator, bool> tmp;
	ft::map<int, std::string> m;
	ft::pair<int, std::string> p = ft::make_pair<int, std::string>(1, "hello");
	m.insert(p);
	p = ft::make_pair<int, std::string>(2, "a");
	m.insert(p);
	p = ft::make_pair<int, std::string>(3, "k");
	m.insert(p);
	tmp = m.insert(ft::make_pair(5, "l"));
	std::cout << "insert complete : pair-first " << tmp.first->first << " pair-second " << tmp.first->second << " true/false " << tmp.second << std::endl;
	tmp = m.insert(ft::make_pair(5, "l2"));
	std::cout << "insert complete : pair-first " << tmp.first->first << " pair-second " << tmp.first->second << " true/false " << tmp.second << std::endl;
	p = ft::make_pair<int, std::string>(4, "i");
	m.insert(p);
	m.insert(ft::pair<int, std::string>(6, "kkk"));
	ft::map<int, std::string>::iterator it = m.begin();
	while (it != m.end())
	{
		std::cout << "original : " << it->first << " : " << it->second << std::endl;
		it++;
	}

	m[5] = "lllllllllllllllllllll";
	it = m.begin();
	while (it != m.end())
	{
		std::cout << "after [ ] : " << it->first << " : " << it->second << std::endl;
		it++;
	}
	ft::map<int, std::string> m2;
	m2.insert(ft::make_pair(99, "kdkd"));
	m2.insert(ft::make_pair(95, "kd"));
	m2.insert(ft::make_pair(96, "k,,d"));
	m.swap(m2);
	it = m.begin();
	while (it != m.end())
	{
		std::cout << "swap, m : " << it->first << " : " << it->second << std::endl;
		it++;
	}
	it = m2.begin();
	while (it != m2.end())
	{
		std::cout << "swap, m2 : " << it->first << " : " << it->second << std::endl;
		it++;
	}

	////////////////
	std::cout << std::endl;
	///////////////

	std::cout << "std===========================\n";
	std::pair<std::map<int, std::string>::iterator, bool> _tmp;
	std::map<int, std::string> _m;
	std::pair<int, std::string> _p = std::make_pair<int, std::string>(1, "hello");
	_m.insert(_p);
	_p = std::make_pair<int, std::string>(2, "a");
	_m.insert(_p);
	_p = std::make_pair<int, std::string>(3, "k");
	_m.insert(_p);
	_tmp = _m.insert(std::make_pair(5, "l"));
	std::cout << "insert complete : pair-first " << _tmp.first->first << " pair-second " << _tmp.first->second << " true/false " << _tmp.second << std::endl;
	_tmp = _m.insert(std::make_pair(5, "l2"));
	std::cout << "insert complete : pair-first " << _tmp.first->first << " pair-second " << _tmp.first->second << " true/false " << _tmp.second << std::endl;
	_p = std::make_pair<int, std::string>(4, "i");
	_m.insert(_p);
	_m.insert(std::pair<int, std::string>(6, "kkk"));
	std::map<int, std::string>::iterator _it = _m.begin();
	while (_it != _m.end())
	{
		std::cout << "original : " << _it->first << " : " << _it->second << std::endl;
		_it++;
	}
	_m[5] = "lllllllllllllllllllll";
	_it = _m.begin();
	while (_it != _m.end())
	{
		std::cout << "after [ ] : " << _it->first << " : " << _it->second << std::endl;
		_it++;
	}
	std::map<int, std::string> _m2;
	_m2.insert(std::make_pair(99, "kdkd"));
	_m2.insert(std::make_pair(95, "kd"));
	_m2.insert(std::make_pair(96, "k,,d"));
	_m.swap(_m2);
	_it = _m.begin();
	while (_it != _m.end())
	{
		std::cout << "swap, _m : " << _it->first << " 2: " << _it->second << std::endl;
		_it++;
	}
	_it = _m2.begin();
	while (_it != _m2.end())
	{
		std::cout << "swap, _m2 : " << _it->first << " 3: " << _it->second << std::endl;
		_it++;
	}

// test dup
	std::cout << "\n====================\n    TEST MAP DUP    \n====================\n\n";
	ft::map<int, int> map_int;
	for (int i = 0; i < INT_MAX / 10000; ++i)
		map_int.insert(ft::make_pair(rand(), rand()));
	int sum = 0;
	for (int i = 0; i < INT_MAX / 1000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "중복된 횟수 : " << sum << std::endl << std::endl;

// leak test
	std::cout << "\n====================\n     TEST LEAK      \n====================\n\n";
	leak_test();
	system("leaks container");
}
