#include "vector.hpp"
#include <vector>

#include <iostream>

class A
{
	public:
		int* a;
		A(int k)
		{
			// std::cout << "==============constructor\n";
			// std::cout << "new : " << this << std::endl;
			a = new int(k);
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
	ft::vector<A> v;
	A a(1);
	A aa(2);
	A b(3);
	A bb(4);
	v.insert(v.begin(), 1, a);
	v.insert(v.begin(), 1, aa);
	std::cout << *(v[0].a) << " " << *(v[1].a) << std::endl;
	v.insert(v.begin() + 1, 1, b);
	v.insert(v.begin(), 1, bb);
	std::cout << *(v[0].a) << " " << *(v[1].a) << " " << *(v[2].a) << " " << *(v[3].a) << std::endl;
}

int main()
{
// test throw
	std::cout << "\n====================\n    TEST VECTOR     \n====================\n\n";
	std::cout << "error test" << std::endl;
	std::vector<int> ori;
	ori.push_back(1);
	try
	{
		ori.reserve(LLONG_MAX);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	ft::vector<int> me;
	me.push_back(1);
	try
	{
		me.reserve(LLONG_MAX);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		ori.at(10);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	me.push_back(1);
	try
	{
		me.at(10);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

// test insert
	std::cout << "\nnormal test===================" << std::endl;
	ft::vector<char> __v;
	__v.push_back('a');
	__v.push_back('b');
	__v.push_back('c');
	__v.insert(__v.begin() + 1, 3, 'k');
	ft::random_access_iterator<char> __v_f = __v.begin();
	ft::random_access_iterator<char> __v_e = __v.end();
	while (__v_f != __v_e)
	{
		std::cout << *__v_f << std::endl;
		__v_f++;
	}

// test copy
	std::cout << "\nnormal(copy) test=============" << std::endl;
	ft::vector<char> testc(__v.begin(), __v.end());
	ft::random_access_iterator<char> testc_f = testc.begin();
	ft::random_access_iterator<char> testc_e = testc.end();
	while (testc_f != testc_e)
	{
		std::cout << *testc_f << std::endl;
		testc_f++;
	}

// test other T
	std::cout << "\nnormal test===================" << std::endl;
	ft::vector<std::string> __v2;
	__v2.push_back("hello");
	__v2.push_back("world");
	__v2.push_back("!!!");
	for (int i = 0; i < (int)__v2.size(); i++)
		std::cout << __v2.data()[i] << std::endl;

std::cout << "\n\n\n";

// test every thing
	std::cout << "\n====================\n  TEST VECTOR FUNC  \n====================\n\n";
	std::cout << "\n===================push back" << std::endl;
	ft::vector<std::string> vec;
	vec.push_back("1");
	vec.push_back("2");
	vec.push_back("3");
	vec.push_back("4");
	vec.push_back("5");
	vec.push_back("6");
	for (ft::random_access_iterator<std::string> it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================insert iterator" << std::endl;
	ft::vector<std::string> vec_insert(vec.begin(), vec.end());
	for (ft::random_access_iterator<std::string> it = vec_insert.begin(); it != vec_insert.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================copy" << std::endl;
	ft::vector<std::string> vec_copy(vec);
	for (ft::random_access_iterator<std::string> it = vec_copy.begin(); it != vec_copy.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================operator =" << std::endl;
	ft::vector<std::string> vec_op;
	vec_op = vec;
	for (ft::random_access_iterator<std::string> it = vec_op.begin(); it != vec_op.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================clear" << std::endl;
	vec.clear();
	std::cout << "\n===================assign" << std::endl;
	vec.assign(13, "test");
	for (ft::random_access_iterator<std::string> it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================assign iterator" << std::endl;
	vec_copy.assign(vec.begin(), vec.end());
	for (ft::random_access_iterator<std::string> it = vec_copy.begin(); it != vec_copy.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================compare std" << std::endl;
	ft::vector<int> vv;
	std::vector<int> vvv;
	for (int i = 10; i < 20; i++)
	{
		vv.push_back(i);
		vvv.push_back(i);
	}
	std::cout << "\n===================at ft" << std::endl;
	for (int i = 0; i < 11; i++)
	{
		try{std::cout << vv.at(i) << " ";}
		catch(std::exception &e) {std::cout << e.what() << " ";}
	}
	std::cout << std::endl;
	std::cout << "\n===================[] ft" << std::endl;
	for (int i = 0; i < 11; i++)
	{
		try{std::cout << vv[i] << " ";}
		catch(std::exception &e) {std::cout << e.what() << " ";}
	}
	std::cout << std::endl;
	std::cout << "\n===================at std" << std::endl;
	for (int i = 0; i < 11; i++)
	{
		try{std::cout << vvv.at(i) << " ";}
		catch(std::exception &e) {std::cout << e.what() << " ";}
	}
	std::cout << std::endl;
	std::cout << "\n===================[] std" << std::endl;
	for (int i = 0; i < 11; i++)
	{
		try{std::cout << vvv[i] << " ";}
		catch(std::exception &e) {std::cout << e.what() << " ";}
	}
	std::cout << std::endl;
	std::cout << "\n===================data ft, std" << std::endl;
	for (int i = 0; i < 11; i++)
	{
		std::cout << vv.data()[i] << " ";
		std::cout << vvv.data()[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "\n===================reverse iterator" << std::endl;
	for (ft::reverse_iterator<ft::random_access_iterator<int> > it = vv.rbegin(); it != vv.rend(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================before clear" << std::endl;
	std::cout << vv.empty() << " " << vv.size() << std::endl;
	vv.clear();
	vvv.clear();
	std::cout << "\n===================after clear" << std::endl;
	std::cout << vv.empty() << " " << vv.size() << std::endl;
	std::cout << "\n===================before reserve" << std::endl;
	std::cout << "\n===================max size ft, std" << std::endl;
	std::cout << vv.max_size() << " " << vvv.max_size() << std::endl;
	std::cout << "\n===================capacity ft, std" << std::endl;
	std::cout << vv.capacity() << " " << vvv.capacity() << std::endl;
	vv.reserve(100);
	vvv.reserve(100);
	std::cout << "\n===================after reserve 100" << std::endl;
	std::cout << "\n===================capacity ft, std" << std::endl;
	std::cout << vv.capacity() << " " << vvv.capacity() << std::endl;
	std::cout << "\n===================size ft, std" << std::endl;
	std::cout << vv.size() << " " << vvv.size() << std::endl;
	vv.reserve(1);
	vvv.reserve(1);
	std::cout << "\n===================after reserve 1" << std::endl;
	std::cout << "\n===================capacity ft, std" << std::endl;
	std::cout << vv.capacity() << " " << vvv.capacity() << std::endl;
	std::cout << "\n===================size ft, std" << std::endl;
	std::cout << vv.size() << " " << vvv.size() << std::endl;
	vv.resize(1);
	vvv.resize(1);
	std::cout << "\n===================after resize 1" << std::endl;
	std::cout << "\n===================capacity ft, std" << std::endl;
	std::cout << vv.capacity() << " " << vvv.capacity() << std::endl;
	std::cout << "\n===================size ft, std" << std::endl;
	std::cout << vv.size() << " " << vvv.size() << std::endl;

	std::cout << "\n===================operator * ft" << std::endl;
	for (ft::random_access_iterator<int> it = vv.begin(); it != vv.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================operator * std" << std::endl;
	for (std::__wrap_iter<int *> it = vvv.begin(); it != vvv.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n\n";
	vv.clear();
	vvv.clear();
	for (int i = 10; i < 20; i++)
	{
		vv.push_back(i);
		vvv.push_back(i);
	}
	vv.insert(vv.begin() + 2, 5);
	vvv.insert(vvv.begin() + 2, 5);
	std::cout << "\n===================insert ft" << std::endl;
	for (ft::random_access_iterator<int> it = vv.begin(); it != vv.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================insert std" << std::endl;
	for (std::__wrap_iter<int *> it = vvv.begin(); it != vvv.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	ft::vector<int> vv2;
	vv2.push_back(5);
	vv2.push_back(5);
	vv2.push_back(5);
	vv2.push_back(5);
	vv2.push_back(5);
	vv2.push_back(5);
	vv.swap(vv2);
	std::cout << "\n===================swap 1" << std::endl;
	for (ft::random_access_iterator<int> it = vv.begin(); it != vv.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "\n===================swap 2" << std::endl;
	for (ft::random_access_iterator<int> it = vv2.begin(); it != vv2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

// leak test
	std::cout << "\n====================\n     TEST LEAK      \n====================\n\n";
	leak_test();
	system("leaks container");
}
