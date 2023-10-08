/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:17:57 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 10:28:50 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_empty_str(char *s)
{
	if (!s)
		return (0);
	if (s[0] != 0)
		return (0);
	return (1);
}

int	is_three(char **color)
{
	int	i;

	i = 0;
	while (color[i])
		i++;
	return (i == 3);
}

int	str_digit(char **color)
{
	int	i;
	int	j;

	j = 0;
	while (j < 3)
	{
		i = 0;
		while (color[j][i])
		{
			if (!ft_isdigit(color[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	atoi_cub(char *s)
{
	int	res;

	if (ft_strlen(s) > 3)
		_error(MAP_ERR);
	res = ft_atoi(s);
	if (res < 0 || res > 255)
		_error(MAP_ERR);
	return (res);
}
