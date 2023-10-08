/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:37:26 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/07 16:20:34 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_w(t_game *game)
{
	game->pos.dx = game->pos.dir_x * MOVE_SPEED;
	game->pos.dy = game->pos.dir_y * MOVE_SPEED;
}

void	key_s(t_game *game)
{
	game->pos.dx = -game->pos.dir_x * MOVE_SPEED;
	game->pos.dy = -game->pos.dir_y * MOVE_SPEED;
}

void	key_a(t_game *game)
{
	game->pos.dx = game->pos.dir_y * MOVE_SPEED;
	game->pos.dy = -game->pos.dir_x * MOVE_SPEED;
}

void	key_d(t_game *game)
{
	game->pos.dx = -game->pos.dir_y * MOVE_SPEED;
	game->pos.dy = game->pos.dir_x * MOVE_SPEED;
}

int	key_press(int key, void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		game->keydown = key;
	else if (key == KEY_LEFT)
		game->pos.rotate = -ROTATE_SPEED;
	else if (key == KEY_RIGHT)
		game->pos.rotate = ROTATE_SPEED;
	else if (key == KEY_F)
		key_f(game);
	else if (key == KEY_ESC)
		exit_game(game);
	return (0);
}
