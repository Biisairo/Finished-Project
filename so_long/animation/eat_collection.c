/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_collection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:47:23 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/11 23:14:13 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	eat_collection(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < game->map->height)
	{
		y = 0;
		while (y < game->map->width)
		{
			if ((game->map->map)[x][y] == 'C')
			{
				if ((size_t)sqrt((y * 32 - game->player.pos[0]) * (y * 32
							- game->player.pos[0])) + ((x * 32
							- game->player.pos[1]) * (x * 32
							- game->player.pos[1])) < 16)
				{
					(game->map->map)[x][y] = 0;
					game->map->collection -= 1;
				}
			}
			y++;
		}
		x++;
	}
}
