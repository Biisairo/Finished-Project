/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_ani.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:54:14 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/11 22:42:06 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	monster_ani(t_game *game)
{
	static int	time;
	size_t		i;

	time++;
	if (time == 160)
		time = 0;
	i = 0;
	while (i < game->monster_cnt)
	{
		monster_ani_walk(game, (game->monster)[i], time / 10);
		monster_change_direction(game, (game->monster) + i);
		i++;
	}
}

void	monster_ani_walk(t_game *game, t_monster monster, int time)
{
	if (monster.direction_state)
		mlx_put_image_to_window(game->mlx, game->win, (monster.img)[time % 4
			+ 4].img, (monster.pos)[0], (monster.pos[1]));
	else
		mlx_put_image_to_window(game->mlx, game->win, (monster.img)[time
			% 4].img, (monster.pos)[0], (monster.pos[1]));
}

void	monster_change_direction(t_game *game, t_monster *monster)
{
	int	x;
	int	y;

	x = monster->pos[1] / 32;
	y = monster->pos[0] / 32;
	if (monster->direction_state == 0)
		monster_move_right(game, monster);
	else
		monster_move_left(game, monster);
}

void	monster_move_right(t_game *game, t_monster *monster)
{
	int	x;
	int	y;

	x = monster->pos[1] / 32;
	y = monster->pos[0] / 32;
	if ((game->map->map)[x][y + 1] == '1' || (game->map->map)[x][y + 1] == 'E')
	{
		if ((monster->pos)[0] + 32 == (y + 1) * 32)
			monster->direction_state = 1;
	}
	else
		monster->pos[0] += 1;
}

void	monster_move_left(t_game *game, t_monster *monster)
{
	int	x;
	int	y;

	x = monster->pos[1] / 32;
	y = monster->pos[0] / 32;
	if ((game->map->map)[x][y - 1] == '1' || (game->map->map)[x][y - 1] == 'E')
	{
		if ((monster->pos)[0] == (y - 1) * 32 + 32)
			monster->direction_state = 0;
		else
			monster->pos[0] -= 1;
	}
	else
		monster->pos[0] -= 1;
}
