#include "main.hpp"

void reserve()
{
	testNamePrint("reserve");

	std::vector<int> std_v;
	ft::vector<int> ft_v;
	print(ft_v, std_v);

	std_v.resize(5);
	ft_v.resize(5);

	for (size_t i = 0; i < ft_v.size(); i++)
	{
		std_v[i] = (i + 1) * 3;
		ft_v[i] = (i + 1) * 3;
	}

	print(ft_v, std_v);


	std_v.reserve(10);
	ft_v.reserve(10);
	print(ft_v, std_v);

	std_v.reserve(3);
	ft_v.reserve(3);
	print(ft_v, std_v);
}
