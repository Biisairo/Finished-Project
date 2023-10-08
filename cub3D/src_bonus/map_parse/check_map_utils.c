/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:31:18 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 11:43:00 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_is_whitespace(char c)
{
	if ((7 < c && c < 14) || c == ' ')
		return (1);
	return (0);
}

void	is_open(char **map, int x, int y)
{
	if (x == 0 || y == 0 || map[x][y + 1] == 0 || map[x + 1] == 0)
		_error(MAP_ERR);
	if (ft_is_whitespace(map[x - 1][y]) || ft_is_whitespace(map[x][y - 1])
		|| ft_is_whitespace(map[x + 1][y]) || ft_is_whitespace(map[x][y + 1]))
		_error(MAP_ERR);
}

int	check_char(char **map, int x, int y, int *player)
{
	if (map[x][y] != '1' && !ft_is_whitespace(map[x][y]))
		is_open(map, x, y);
	if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W'
		|| map[x][y] == 'E')
		(*player)++;
	else if (map[x][y] == 'V' || map[x][y] == 'H'
		|| map[x][y] == '0' || map[x][y] == '1'
		|| ft_is_whitespace(map[x][y]))
		;
	else
		return (1);
	return (0);
}
