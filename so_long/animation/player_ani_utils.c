/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_ani_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:54:14 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/09 11:24:05 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	player_ani_idle(t_game *game, int time)
{
	if (game->player.direction_state)
		mlx_put_image_to_window(game->mlx, game->win, (game->player.img)[time
			% 2 + 2].img, (game->player.pos)[0], (game->player.pos[1]));
	else
		mlx_put_image_to_window(game->mlx, game->win, (game->player.img)[time
			% 2].img, (game->player.pos)[0], (game->player.pos[1]));
}

void	player_ani_walk(t_game *game, int time)
{
	if (game->player.direction_state)
		mlx_put_image_to_window(game->mlx, game->win, (game->player.img)[time
			% 8 + 12].img, (game->player.pos)[0], (game->player.pos[1]));
	else
		mlx_put_image_to_window(game->mlx, game->win, (game->player.img)[time
			% 8 + 4].img, (game->player.pos)[0], (game->player.pos[1]));
}

void	player_ani_jump(t_game *game, int jump)
{
	if (jump < 8)
	{
		if (game->player.direction_state)
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[jump + 28].img, (game->player.pos)[0],
				(game->player.pos[1]));
		else
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[jump + 20].img, (game->player.pos)[0],
				(game->player.pos[1]));
	}
	else
	{
		if (game->player.direction_state)
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[35].img, (game->player.pos)[0],
				(game->player.pos[1]));
		else
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[27].img, (game->player.pos)[0],
				(game->player.pos[1]));
	}
}

void	player_ani_down(t_game *game, int down)
{
	if (down < 8)
	{
		if (game->player.direction_state)
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[down + 44].img, (game->player.pos)[0],
				(game->player.pos[1]));
		else
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[down + 36].img, (game->player.pos)[0],
				(game->player.pos[1]));
	}
	else
	{
		if (game->player.direction_state)
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[51].img, (game->player.pos)[0],
				(game->player.pos[1]));
		else
			mlx_put_image_to_window(game->mlx, game->win,
				(game->player.img)[43].img, (game->player.pos)[0],
				(game->player.pos[1]));
	}
}
