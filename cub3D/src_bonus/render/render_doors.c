/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:17:19 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/05 11:44:07 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	get_door_color(t_game *game, t_ray *ray, double wall_x, double wall_y)
{
	double	shift;
	t_door	*door;

	door = get_door_by_ray(game, ray);
	shift = game->map.door_img.img_width * door->open_state;
	if (ray->wall_side == 0 || ray->wall_side == 3)
		shift = -shift;
	wall_x += shift;
	if (wall_x >= game->map.door_img.img_width || wall_x < 0)
		return (-1);
	return (get_color(&game->map.door_img, wall_x, wall_y));
}

void	draw_door(t_game *game, t_ray *ray, t_draw_info *info, t_img *img)
{
	int	y;
	int	color;

	y = info->wall_start;
	while (y < info->wall_end)
	{
		color = get_door_color(game, ray, info->wall_x, info->wall_y);
		if (color >= 0)
			set_color(img, ray->x, y, color);
		info->wall_y += info->step;
		y++;
	}
}

t_door	*draw_if_door(t_game *game, t_ray *ray, t_img *img)
{
	t_door		*door;
	t_draw_info	info;

	door = get_door_by_ray(game, ray);
	if (!door)
		return (NULL);
	info = calc_draw_info(game, ray);
	if (get_door_color(game, ray, info.wall_x, info.wall_y) == -1)
		return (NULL);
	else
	{
		draw_door(game, ray, &info, img);
		return (door);
	}
}

void	draw_doors(t_game *game, t_ray *ray, t_img *img)
{
	t_door	*res;

	while (1)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->wall_side = 2;
			if (ray->step_x < 0)
				ray->wall_side = 3;
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->wall_side = 0;
			if (ray->step_y < 0)
				ray->wall_side = 1;
		}
		res = draw_if_door(game, ray, img);
		if (res || game->map.map[ray->map_y][ray->map_x] == '1')
			return ;
	}
}
