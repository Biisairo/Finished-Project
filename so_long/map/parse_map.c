/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:47:07 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/12 08:51:26 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	parse_map(t_game *game, char *map_name)
{
	t_map	**map;

	map = &(game->map);
	*map = ft_malloc(sizeof(t_map));
	if (!(*map))
		ft_error(0, game);
	init_map(*map);
	if (make_map(*map, map_name))
	{
		clear_map(map);
		ft_error(0, game);
	}
	map_error(game);
	start_pos(*map);
	return (0);
}

void	map_error(t_game *game)
{
	if (!game->map->map)
		ft_error(11, game);
	if (game->map->height == 0)
		ft_error(12, game);
	if (find_width(game->map))
		ft_error(12, game);
	if (set_map(game->map))
		ft_error(13, game);
	if (check_map(game->map))
		ft_error(14, game);
	if (check_arg(game->map))
		ft_error(15, game);
}

void	init_map(t_map *map)
{
	map->map = 0;
	map->height = 0;
	map->width = 0;
	map->collection = 0;
	map->player = 0;
	map->exit = 0;
	(map->start_pos)[0] = 0;
	(map->start_pos)[1] = 0;
}

void	clear_map(t_map **map)
{
	size_t	i;

	i = 0;
	if (!((*map)->map))
		return ;
	while (i < (*map)->height)
	{
		ft_free(((*map)->map)[i]);
		i++;
	}
	ft_free((*map)->map);
	*map = 0;
}
