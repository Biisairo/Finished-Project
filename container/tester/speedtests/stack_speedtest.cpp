/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_speedtest.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:35:40 by pohl              #+#    #+#             */
/*   Updated: 2023/02/17 12:05:20 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <cstdlib>

#ifndef IS_STD
# define IS_STD 0
#endif

#if IS_STD == 1
	#include <stack>
	namespace ft = std;
#else
	#include "../stack.hpp"
#endif

int	main( void )
{
	ft::stack<int>	testedStack;
	int				numberOfPushes = 100000000;

	for (int i = 0; i < numberOfPushes; i++)
		testedStack.push(i);
	for (int i = 0; i < numberOfPushes; i++)
		testedStack.pop();
	return 0;
}
