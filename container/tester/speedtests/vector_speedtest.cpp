/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_speedtest.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:35:40 by pohl              #+#    #+#             */
/*   Updated: 2023/02/18 13:38:39 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <cstdlib>
#include <iostream>

#ifndef IS_STD
# define IS_STD 0
#endif

#if IS_STD == 1
	#include <vector>
	namespace ft = std;
#else
	#include "../vector.hpp"
#endif

int	main( void )
{
	ft::vector<int>	testedVector;
	size_t			numberOfPushes = 10000;

	for (size_t i = 0; i < numberOfPushes; i++)
		testedVector.insert(testedVector.begin(), i);
	testedVector.clear();
	return 0;
}
