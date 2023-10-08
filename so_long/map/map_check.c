/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:47:07 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/12 08:44:04 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->width)
	{
		if ((map->map)[0][i] != '1')
			return (1);
		if ((map->map)[map->height - 1][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if ((map->map)[i][0] != '1')
			return (1);
		if ((map->map)[i][map->width - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	start_pos(t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if ((map->map)[x][y] == 'P')
			{
				(map->start_pos)[0] = x;
				(map->start_pos)[1] = y;
			}
			if ((map->map)[x][y] == 'E')
			{
				(map->end_pos)[0] = x;
				(map->end_pos)[1] = y;
			}
			y++;
		}
		x++;
	}
}

int	set_map(t_map *map)
{
	size_t	h;
	size_t	w;

	h = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			if ((map->map)[h][w] == 'C')
				map->collection += 1;
			if ((map->map)[h][w] == 'E')
				map->exit += 1;
			if ((map->map)[h][w] == 'P')
				map->player += 1;
			w++;
		}
		h++;
	}
	if (map->collection < 1 || map->exit != 1 || map->player != 1)
		return (1);
	return (0);
}

size_t	find_width(t_map *map)
{
	size_t	i;

	map->width = ft_strlen((map->map)[0]);
	i = 0;
	while (i < map->height)
	{
		if (ft_strlen((map->map)[i]) != map->width)
			return (1);
		i++;
	}
	return (0);
}

size_t	check_arg(t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (!((map->map)[x][y] == '1' || (map->map)[x][y] == '0'
					|| (map->map)[x][y] == 'E' || (map->map)[x][y] == 'C'
					|| (map->map)[x][y] == 'P' || (map->map)[x][y] == 'M'))
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}
