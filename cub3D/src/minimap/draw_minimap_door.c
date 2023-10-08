/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_door.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:29 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 10:28:50 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	change_door(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'v')
				change_map_door_v(&map->map_img, i + 4, j + 4);
			else if (map->map[i][j] == 'h')
				change_map_door_h(&map->map_img, i + 4, j + 4);
			else if (map->map[i][j] == 'H')
				put_h(&map->map_img, i + 4, j + 4);
			else if (map->map[i][j] == 'V')
				put_v(&map->map_img, i + 4, j + 4);
			j++;
		}
		i++;
	}
}

void	change_map_door_v(t_map_img *map, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 20)
		{
			if (i == 0 || i == 3 || j == 0 || j == 19)
				pixel_put(map, x * 20 + i, y * 20 + j, 0x33000000);
			else
				pixel_put(map, x * 20 + i, y * 20 + j, 0x3300FF00);
			j++;
		}
		i++;
	}
}

void	change_map_door_h(t_map_img *map, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 4)
		{
			if (i == 0 || i == 19 || j == 0 || j == 3)
				pixel_put(map, x * 20 + i, y * 20 + j, 0x33000000);
			else
				pixel_put(map, x * 20 + i, y * 20 + j, 0x3300FF00);
			j++;
		}
		i++;
	}
}
