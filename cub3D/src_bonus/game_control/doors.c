/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:23:50 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/05 11:43:04 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_door	*get_door(t_game *game, int x, int y)
{
	t_door	*res;

	res = game->map.doors;
	while (res)
	{
		if (res->x == x && res->y == y)
			return (res);
		res = res->next;
	}
	return (NULL);
}

t_door	*get_door_by_ray(t_game *game, t_ray *ray)
{
	t_door	*door;

	if (ray->wall_side == 1)
	{
		door = get_door(game, ray->map_x, ray->map_y + 1);
		if (door && door->dir == HORIZONTAL)
			return (door);
	}
	else if (ray->wall_side == 3)
	{
		door = get_door(game, ray->map_x + 1, ray->map_y);
		if (door && door->dir == VERTICAL)
			return (door);
	}
	else
	{
		door = get_door(game, ray->map_x, ray->map_y);
		if (door && ((ray->wall_side == 0 && door->dir == HORIZONTAL)
				|| (ray->wall_side == 2 && door->dir == VERTICAL)))
			return (door);
	}
	return (NULL);
}

void	update_doors(t_game *game)
{
	t_door	*door;

	door = game->map.doors;
	while (door)
	{
		if (door->open_speed)
		{
			door->open_state += door->open_speed;
			if (door->open_state <= 0)
			{
				door->open_state = 0;
				door->open_speed = 0;
			}
			else if (door->open_state >= 1)
			{
				door->open_state = 1;
				door->open_speed = 0;
				game->map.map[door->y][door->x] += 'a' - 'A';
			}
		}
		door = door->next;
	}
}

void	proc_door(t_game *game, int x, int y)
{
	t_door	*door;

	door = get_door(game, x, y);
	if (door->open_speed == 0 && door->open_state == 0)
		door->open_speed = DOOR_SPEED;
	else if (door->open_speed == 0 && door->open_state == 1)
	{
		game->map.map[y][x] += 'A' - 'a';
		door->open_speed = -DOOR_SPEED;
	}
	else if (door->open_speed > 0)
		door->open_speed = -DOOR_SPEED;
	else if (door->open_speed < 0)
		door->open_speed = DOOR_SPEED;
}

void	key_f(t_game *game)
{
	int	front_x;
	int	front_y;

	if (ft_absd(game->pos.dir_x) >= ft_absd(game->pos.dir_y))
	{
		front_x = (int)(game->pos.x + ft_dir(game->pos.dir_x));
		front_y = (int)(game->pos.y);
	}
	else
	{
		front_x = (int)(game->pos.x);
		front_y = (int)(game->pos.y + ft_dir(game->pos.dir_y));
	}
	if (game->map.map[front_y][front_x] == 'V'
		|| game->map.map[front_y][front_x] == 'v'
		|| game->map.map[front_y][front_x] == 'H'
		|| game->map.map[front_y][front_x] == 'h')
		proc_door(game, front_x, front_y);
}
