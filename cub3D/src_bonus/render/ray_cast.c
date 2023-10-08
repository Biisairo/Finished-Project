/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:55:28 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/06 11:00:01 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ray_draw(t_game *game, t_ray *ray, t_draw_info *info, t_img *img)
{
	int	y;

	y = 0;
	while (y < info->wall_start)
	{
		set_color(img, ray->x, y, game->map.floor[1].color);
		y++;
	}
	y = info->wall_start;
	while (y < info->wall_end)
	{
		set_color(img, ray->x, y, get_color(&game->map.wall[ray->wall_side],
				info->wall_x, info->wall_y));
		info->wall_y += info->step;
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		set_color(img, ray->x, y, game->map.floor[0].color);
		y++;
	}
}

void	ray_cast(t_game	*game)
{
	int			x;
	t_ray		ray;
	t_draw_info	draw_info;
	t_img		img;

	x = 0;
	img = create_img(game);
	while (x < SCREEN_WIDTH)
	{
		ray = init_ray(game, x);
		find_wall(game, &ray);
		draw_info = calc_draw_info(game, &ray);
		ray_draw(game, &ray, &draw_info, &img);
		ray = init_ray(game, x);
		draw_doors(game, &ray, &img);
		x++;
	}
	draw_gun(game, &img);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}
