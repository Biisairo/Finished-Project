/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:31:18 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 11:43:00 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	add_door(t_game *game, int x, int y, char c)
{
	t_door	*new_door;

	new_door = ft_malloc(sizeof(t_door));
	if (!new_door)
		_error(MALLOC_ERR);
	new_door->x = x;
	new_door->y = y;
	if (c == 'V')
		new_door->dir = VERTICAL;
	else
		new_door->dir = HORIZONTAL;
	new_door->open_speed = 0;
	new_door->open_state = 0;
	new_door->next = game->map.doors;
	game->map.doors = new_door;
}

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
			if (map[x][y] == 'V' || map[x][y] == 'H')
				add_door(game, y, x, map[x][y]);
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
