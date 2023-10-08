/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:30:08 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 11:42:53 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	put_pixel_to_map(t_map_img *map_img, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				put_blk(map_img, i + 4, j + 4);
			else
				put_back(map_img, i + 4, j + 4);
			if (map[i][j] == 'H')
				put_h(map_img, i + 4, j + 4);
			if (map[i][j] == 'V')
				put_v(map_img, i + 4, j + 4);
			j++;
		}
		i++;
	}
}

void	put_blk(t_map_img *map_img, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			if (i == 0 || i == 19 || j == 0 || j == 19)
				pixel_put(map_img, x * 20 + i, y * 20 + j, 0x33000000);
			else
				pixel_put(map_img, x * 20 + i, y * 20 + j, 0x33FFFFFF);
			j++;
		}
		i++;
	}
}

void	put_back(t_map_img *map_img, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			pixel_put(map_img, x * 20 + i, y * 20 + j, 0x55000000);
			j++;
		}
		i++;
	}
}

void	put_h(t_map_img *map_img, int y, int x)
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
				pixel_put(map_img, x * 20 + i, y * 20 + j, 0x33000000);
			else
				pixel_put(map_img, x * 20 + i, y * 20 + j, 0x33FFFFFF);
			j++;
		}
		i++;
	}
}

void	put_v(t_map_img *map_img, int y, int x)
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
				pixel_put(map_img, x * 20 + i, y * 20 + j, 0x33000000);
			else
				pixel_put(map_img, x * 20 + i, y * 20 + j, 0x33FFFFFF);
			j++;
		}
		i++;
	}
}
