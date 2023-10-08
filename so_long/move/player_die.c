/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:57:33 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 12:58:53 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	player_die(t_game *game)
{
	t_monster	p;
	size_t		i;
	size_t		dist;

	i = 0;
	while (i < game->monster_cnt)
	{
		p = game->monster[i];
		dist = (size_t)sqrt((p.pos[0] - game->player.pos[0]) * (p.pos[0]
					- game->player.pos[0])) + ((p.pos[1] - game->player.pos[1])
				* (p.pos[1] - game->player.pos[1]));
		if (dist < 32)
		{
			if (game->player.life)
				game->player.life -= 1;
		}
		i++;
	}
}
