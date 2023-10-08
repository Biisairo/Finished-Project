/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_drop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:27:58 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 12:37:05 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	player_drop(t_game *game)
{
	int			x;
	int			y;
	int static	i;
	int			move;

	x = game->player.pos[1] / 32;
	y = game->player.pos[0] / 32;
	move = 0;
	if (on_ground(game, x, y))
	{
		i = 0;
		game->player.drop_state = 0;
	}
	if (game->player.jump_state == 0 && !on_ground(game, x, y))
	{
		move = drop_process(game, i);
		if (i < 24)
			i++;
	}
	return (move);
}

int	drop_branch(t_game *game, int *i, int x, int y)
{
	if ((game->map->map)[x + 1][y] == '1')
	{
		if ((game->player.pos)[1] + 32 == (x + 1) * 32)
		{
			*i = 0;
			return (1);
		}
	}
	if ((game->map->map)[x + 1][y + 1] == '1' && (game->player.pos)[0] % 32)
	{
		if ((game->player.pos)[1] + 32 == (x + 1) * 32)
		{
			*i = 0;
			return (1);
		}
	}
	return (0);
}

int	drop_process(t_game *game, int i)
{
	if (i < 4)
	{
		game->player.pos[1] += 1;
		return (1);
	}
	else if (i < 8)
	{
		game->player.pos[1] += 2;
		return (2);
	}
	else if (i < 12)
	{
		game->player.pos[1] += 3;
		return (3);
	}
	else
		drop_process2(game, i);
	return (0);
}

int	drop_process2(t_game *game, int i)
{
	if (i < 16)
	{
		game->player.pos[1] += 4;
		return (4);
	}
	else if (i < 20)
	{
		game->player.pos[1] += 6;
		return (6);
	}
	else
	{
		game->player.pos[1] += 8;
		return (8);
	}
	return (0);
}
