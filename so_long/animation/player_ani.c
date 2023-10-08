/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_ani.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:54:14 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/11 23:17:01 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	player_ani(t_game *game)
{
	static int	time;
	static int	down;
	static int	jump;

	time++;
	if (time == 160)
		time = 0;
	player_ani_1(game, &time, &down, &jump);
}

void	player_ani_1(t_game *game, int *time, int *down, int *jump)
{
	if (game->player.life == 0)
	{
		jump = 0;
		player_ani_down(game, (*down) / 3);
		if (*down < 24)
			*down += 1;
		mlx_string_put(game->mlx, game->win, game->player.pos[0] + 34,
			game->player.pos[1] + 16, 0x00FFFFFF, "You Die");
	}
	else if (game->player.down_state == 1)
	{
		jump = 0;
		player_ani_down(game, (*down) / 1);
		if (*down < 8)
			*down += 1;
	}
	else if (game->player.move_state == 0 && game->player.jump_state == 0)
	{
		*down = 0;
		*jump = 0;
		player_ani_idle(game, (*time) / 10);
	}
	else
		player_ani_2(game, time, down, jump);
}

void	player_ani_2(t_game *game, int *time, int *down, int *jump)
{
	if (game->player.jump_state == 1)
	{
		*down = 0;
		player_ani_jump(game, (*jump) / 7);
		if (*jump < 56)
			*jump += 1;
	}
	else if (game->player.move_state == 1)
	{
		*down = 0;
		*jump = 0;
		player_ani_walk(game, (*time) / 10);
	}
}
