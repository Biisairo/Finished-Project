/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:01:25 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 11:24:42 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	jump(t_game *game)
{
	int			x;
	int			y;
	static int	i;
	int			move;

	x = game->player.pos[1] / 32;
	y = game->player.pos[0] / 32;
	move = 0;
	if (!on_ground(game, x, y) && i == 0)
	{
		game->player.jump_state = 0;
		i = 0;
		return (0);
	}
	if (jump_branch(game, &i, x, y))
		return (0);
	move = jump_process(game, i);
	i++;
	if (i == 3 * 32 / 4)
	{
		game->player.jump_state = 0;
		i = 0;
	}
	return (move);
}

int	jump_branch(t_game *game, int *i, int x, int y)
{
	if ((game->map->map)[x - 1][y] == '1')
	{
		if ((game->player.pos)[1] == (x - 1) * 32 + 32)
		{
			game->player.jump_state = 0;
			*i = 0;
			return (1);
		}
	}
	if ((game->map->map)[x - 1][y + 1] == '1' && (game->player.pos)[0] % 32)
	{
		if ((game->player.pos)[1] == (x - 1) * 32 + 32)
		{
			game->player.jump_state = 0;
			*i = 0;
			return (1);
		}
	}
	return (0);
}

int	jump_process(t_game *game, int i)
{
	if (i < 4)
	{
		game->player.pos[1] -= 8;
		return (8);
	}
	else if (i < 8)
	{
		game->player.pos[1] -= 6;
		return (6);
	}
	else if (i < 12)
	{
		game->player.pos[1] -= 4;
		return (4);
	}
	else
		jump_process2(game, i);
	return (0);
}

int	jump_process2(t_game *game, int i)
{
	if (i < 16)
	{
		game->player.pos[1] -= 3;
		return (3);
	}
	else if (i < 20)
	{
		game->player.pos[1] -= 2;
		return (2);
	}
	else if (i < 24)
	{
		game->player.pos[1] -= 1;
		return (1);
	}
	return (0);
}

int	on_ground(t_game *game, int x, int y)
{
	if ((game->map->map)[x + 1][y] == '1')
	{
		if ((game->player.pos)[1] + 32 == (x + 1) * 32)
			return (1);
	}
	if ((game->map->map)[x + 1][y + 1] == '1' && (game->player.pos)[0] % 32)
	{
		if ((game->player.pos)[1] + 32 == (x + 1) * 32)
			return (1);
	}
	return (0);
}
