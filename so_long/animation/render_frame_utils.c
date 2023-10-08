/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:55:19 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 13:26:37 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	end_game(t_game *game)
{
	size_t	dist;

	dist = (size_t)sqrt((((game->map->end_pos)[1] * 32 - game->player.pos[0])
				* ((game->map->end_pos)[1] * 32 - game->player.pos[0]))
			+ (((game->map->end_pos)[0] * 32 - game->player.pos[1])
				* ((game->map->end_pos)[0] * 32 - game->player.pos[1])));
	if (dist < 16 && game->map->collection == 0)
		game->end = 1;
	if (game->map->collection == 0 && game->end == 1)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_string_put(game->mlx, game->win, 2, 16, 0x00FFFFFF, "-CLEAR-");
	}
}

void	put_move_cnt(t_game *game, int move_cnt)
{
	char	s[30];
	char	*n;

	s[0] = 0;
	n = ft_itoa(move_cnt);
	ft_strlcat(s, "Move : ", 30);
	ft_strlcat(s, n, 30);
	ft_free(n);
	mlx_string_put(game->mlx, game->win, 2, 16, 0x00FFFFFF, s);
}
