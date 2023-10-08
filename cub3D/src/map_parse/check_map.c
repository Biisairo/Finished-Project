/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:31:18 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 11:57:42 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_map(t_game *game)
{
	int		x;
	int		y;
	char	**map;
	int		player;
	int		ect;

	map = game->map.map;
	player = 0;
	ect = 0;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y] != 0 && map[x][y] != '\n')
		{
			ect += check_char(map, x, y, &player);
			set_pos(game, map[x][y], x, y);
			y++;
		}
		x++;
	}
	if (player != 1 || ect != 0 || game->map.dir == 0)
		_error(MAP_ERR);
}

void	set_pos(t_game *game, char pos, int x, int y)
{
	if (pos == 'N' || pos == 'S' || pos == 'W' || pos == 'E')
	{
		game->pos.x = y + 0.5;
		game->pos.y = x + 0.5;
		game->map.dir = pos;
	}
}
