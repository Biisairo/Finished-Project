/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:29 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 12:00:32 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_game *game)
{
	make_clean(&game->minimap, 180, 120);
	put_pixel(&game->map.map_img, &game->minimap, game->pos.x, game->pos.y);
	put_dir(game);
	put_player(&game->minimap);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 20, 340);
}

void	put_pixel(t_map_img *map, t_map_img *mini, double x, double y)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = 80 + round(x * 20) - 90;
	start_y = 80 + round(y * 20) - 60;
	i = 0;
	while (i < 180)
	{
		j = 0;
		while (j < 120)
		{
			pixel_put(mini, i, j, pixel_get(map, start_x + i, start_y + j));
			j++;
		}
		i++;
	}
}

void	put_player(t_map_img *mini)
{
	int	i;
	int	j;

	i = 87;
	while (i < 93)
	{
		j = 57;
		while (j < 63)
		{
			if (!((i == 87 && j == 57) || (i == 87 && j == 62) || (i == 92
						&& j == 57) || (i == 92 && j == 62)))
				pixel_put(mini, i, j, 0x0000FF00);
			j++;
		}
		i++;
	}
}

void	put_dir(t_game *game)
{
	float	x;
	float	y;
	float	theta;
	int		i;

	theta = (M_PI / 6) * -1;
	while (theta <= M_PI / 6)
	{
		x = game->pos.dir_x * cos(theta) - game->pos.dir_y * sin(theta);
		y = game->pos.dir_x * sin(theta) + game->pos.dir_y * cos(theta);
		i = 0;
		while (i < 20)
		{
			pixel_put(&game->minimap, 90 + x * i, 60 + y * i, 0xAA00FF00);
			i++;
		}
		theta += M_PI / 37;
	}
}
