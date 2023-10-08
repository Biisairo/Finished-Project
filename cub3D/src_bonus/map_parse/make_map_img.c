/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:30:08 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/06 11:46:19 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	make_map_img(t_game *game)
{
	int			w;
	int			h;

	get_wh(game->map.map, &w, &h);
	game->map.map_img.img = mlx_new_image(game->mlx,
			((w + 8) * 20), ((h + 8) * 20));
	if (!game->map.map_img.img)
		_error(MLX_ERR);
	game->map.map_img.addr = mlx_get_data_addr(game->map.map_img.img,
			& game->map.map_img.bits_per_pixel,
			& game->map.map_img.line_length,
			& game->map.map_img.endian);
	make_clean(&game->map.map_img, (w + 8) * 20, (h + 8) * 20);
	put_pixel_to_map(&game->map.map_img, game->map.map);
}

void	get_wh(char **map, int *w, int *h)
{
	int	ww;

	*h = 0;
	while (map[*h])
	{
		ww = 0;
		while (map[*h][ww])
			ww++;
		if (*w < ww)
			*w = ww;
		(*h)++;
	}
}

void	make_clean(t_map_img *map_img, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			pixel_put(map_img, i, j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}
