/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:49:34 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/12 08:56:58 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_game(t_game *game, char *mapfile)
{
	char	*map;

	init_game_utils(game);
	map = ft_malloc(ft_strlen(mapfile) + 15);
	if (!map)
		ft_error(0, game);
	map[0] = 0;
	ft_strlcat(map, "./mapfile/", ft_strlen(mapfile) + 15);
	ft_strlcat(map, mapfile, ft_strlen(mapfile) + 15);
	ft_strlcat(map, ".ber", ft_strlen(mapfile) + 15);
	parse_map(game, map);
	ft_free(map);
	game->width = (game->map->width) * 32;
	game->height = (game->map->height) * 32;
	game->mlx = mlx_init();
	if (!(game->mlx))
		ft_error(-1, game);
	game->win = mlx_new_window(game->mlx, game->width, game->height, "GAME");
	if (!(game->win))
		ft_error(-1, game);
	load_player(game);
	load_map(game);
	load_collection(game);
	load_monster(game);
}

void	init_game_utils(t_game *game)
{
	game->mlx = 0;
	game->win = 0;
	game->end = 0;
}
