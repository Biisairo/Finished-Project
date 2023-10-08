/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:17:14 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/05 11:43:57 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	calc_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (game->pos.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = (ray->map_x + 1.0 - game->pos.x) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (game->pos.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = (ray->map_y + 1.0 - game->pos.y) * ray->delta_y;
	}
}

t_ray	init_ray(t_game *game, int x)
{
	t_ray	res;

	res.x = x;
	res.cam_x = 2 * x / (double)SCREEN_WIDTH - 1;
	res.ray_x = game->pos.dir_x + game->pos.plane_x * res.cam_x;
	res.ray_y = game->pos.dir_y + game->pos.plane_y * res.cam_x;
	res.map_x = (int)game->pos.x;
	res.map_y = (int)game->pos.y;
	res.delta_x = ft_absd(1 / res.ray_x);
	res.delta_y = ft_absd(1 / res.ray_y);
	calc_dist(game, &res);
	return (res);
}

void	find_wall(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			if (ray->step_x >= 0)
				ray->wall_side = 2;
			else
				ray->wall_side = 3;
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			if (ray->step_y >= 0)
				ray->wall_side = 0;
			else
				ray->wall_side = 1;
		}
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			return ;
	}
}

void	calc_line_info(t_game *game, t_ray *ray,
	t_draw_info *info, double wall_dist)
{
	info->line_height = (int)(SCREEN_HEIGHT / wall_dist);
	info->wall_start = SCREEN_HEIGHT / 2 - info->line_height / 2;
	info->wall_end = SCREEN_HEIGHT / 2 + info->line_height / 2;
	if (info->wall_start < 0)
		info->wall_start = 0;
	if (info->wall_end >= SCREEN_HEIGHT)
		info->wall_end = SCREEN_HEIGHT - 1;
	info->step = game->map.wall[ray->wall_side].img_height
		/ (double)info->line_height;
	info->wall_y = (info->wall_start - SCREEN_HEIGHT / 2
			+ info->line_height / 2) * info->step;
}

t_draw_info	calc_draw_info(t_game *game, t_ray *ray)
{
	double		wall_dist;
	t_draw_info	res;

	if (ray->wall_side >= 2)
	{
		wall_dist = (ray->map_x - game->pos.x + (1 - ray->step_x) / 2)
			/ ray->ray_x;
		res.wall_x = game->pos.y + wall_dist * ray->ray_y;
	}
	else
	{
		wall_dist = (ray->map_y - game->pos.y + (1 - ray->step_y) / 2)
			/ ray->ray_y;
		res.wall_x = game->pos.x + wall_dist * ray->ray_x;
	}
	res.wall_x -= floor(res.wall_x);
	res.wall_width = game->map.wall[ray->wall_side].img_width;
	res.wall_x = (int)(res.wall_x * (double)res.wall_width);
	if (ray->wall_side == 0 || ray->wall_side == 3)
		res.wall_x = res.wall_width - res.wall_x - 1;
	calc_line_info(game, ray, &res, wall_dist);
	return (res);
}
