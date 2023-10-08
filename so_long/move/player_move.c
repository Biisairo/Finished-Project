/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:01:25 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 12:31:27 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	player_move(t_game *game)
{
	int	move;

	move = 0;
	move += player_drop(game);
	if (game->player.jump_state == 1 && game->player.life)
	{
		game->player.drop_state = 0;
		move += jump(game);
	}
	if (game->player.move_state == 1 && game->player.life)
	{
		if (game->player.direction_state == 0)
			move += move_right(game);
		else if (game->player.direction_state == 1)
			move += move_left(game);
	}
	player_die(game);
	return (move);
}

int	move_right(t_game *game)
{
	int	x;
	int	y;

	x = game->player.pos[1] / 32;
	y = game->player.pos[0] / 32;
	if ((game->map->map)[x][y + 1] == '1')
		if ((game->player.pos)[0] + 32 == (y + 1) * 32)
			return (0);
	if ((game->map->map)[x + 1][y + 1] == '1' && (game->player.pos)[1] % 32)
		if ((game->player.pos)[0] + 32 == (y + 1) * 32)
			return (0);
	game->player.pos[0] += 2;
	return (2);
}

int	move_left(t_game *game)
{
	int	x;
	int	y;

	x = game->player.pos[1] / 32;
	y = game->player.pos[0] / 32;
	if ((game->map->map)[x][y - 1] == '1')
		if ((game->player.pos)[0] == (y - 1) * 32 + 32)
			return (0);
	if ((game->map->map)[x + 1][y - 1] == '1' && (game->player.pos)[1] % 32)
		if ((game->player.pos)[0] == (y - 1) * 32 + 32)
			return (0);
	game->player.pos[0] -= 2;
	return (2);
}
