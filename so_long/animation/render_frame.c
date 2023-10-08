/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:55:19 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/11 22:42:24 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	render_frame(t_game *game)
{
	static size_t	move;
	static size_t	move_cnt;

	if (game->map->collection != 0 || game->end != 1)
	{
		mlx_clear_window(game->mlx, game->win);
		eat_collection(game);
		render_map(game);
		move += player_move(game);
		if (move > 31)
		{
			move_cnt++;
			move = 0;
			ft_printf("move : %u\n", move_cnt);
		}
		render_collection(game);
		render_gate(game);
		player_ani(game);
		monster_ani(game);
		put_move_cnt(game, move_cnt);
	}
	end_game(game);
	return (0);
}

void	render_map(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < game->map->height)
	{
		y = 0;
		while (y < game->map->width)
		{
			if ((game->map->map)[x][y] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->img[0].img, y * 32, x * 32);
			else
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->img[1].img, y * 32, x * 32);
			y++;
		}
		x++;
	}
}

void	render_collection(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < game->map->width)
	{
		y = 0;
		while (y < game->map->height)
		{
			if ((game->map->map)[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->collection.img, x * 32, y * 32);
			y++;
		}
		x++;
	}
}

void	render_gate(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < game->map->width)
	{
		y = 0;
		while (y < game->map->height)
		{
			if ((game->map->map)[y][x] == 'E')
			{
				if (game->map->collection)
					mlx_put_image_to_window(game->mlx, game->win,
						(game->map->img)[2].img, x * 32, y * 32);
				else
					mlx_put_image_to_window(game->mlx, game->win,
						(game->map->img)[3].img, x * 32, y * 32);
			}
			y++;
		}
		x++;
	}
}
