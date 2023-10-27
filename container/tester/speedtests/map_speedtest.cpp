/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_speedtest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:02:27 by pohl              #+#    #+#             */
/*   Updated: 2023/02/17 12:05:14 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef IS_STD
# define IS_STD 0
#endif

#if IS_STD == 1
	#include <map>
	namespace ft = std;
#else
	#include "../map.hpp"
#endif

int main( void )
{
	ft::map<int, char>				testedMap;
	ft::map<int, char>::iterator	it, ite;

	size_t				numberOfPushes = 5000000;

	for (size_t i = 0; i < numberOfPushes; i++)
		testedMap.insert(ft::make_pair(i, 'a'));
	it = testedMap.begin();
	ite = testedMap.end();
	while (it != ite)
	{
		it++;
	}
	testedMap.clear();
	return 0;
}
