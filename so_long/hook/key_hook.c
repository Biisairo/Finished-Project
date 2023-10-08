/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:49:18 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 12:31:33 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		exit_mlx(keycode, game);
	if (keycode == 1)
	{
		if (game->player.life)
			game->player.direction_state = 1;
		game->player.move_state = 1;
	}
	else if (keycode == 2)
	{
		if (game->player.life)
			game->player.direction_state = 0;
		game->player.move_state = 1;
	}
	else if (keycode == 12)
	{
		if (game->player.jump_state != 1 && game->player.drop_state != 1)
			game->player.jump_state = 1;
	}
	else if (keycode == 6)
		game->player.down_state = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 1)
	{
		game->player.move_state = 0;
	}
	else if (keycode == 2)
	{
		game->player.move_state = 0;
	}
	else if (keycode == 6)
	{
		game->player.down_state = 0;
	}
	return (0);
}

int	exit_mlx(int keycode, t_game *game)
{
	if (keycode == 53)
		mlx_destroy_window(game->mlx, game->win);
	ft_clear();
	exit(0);
	return (0);
}
