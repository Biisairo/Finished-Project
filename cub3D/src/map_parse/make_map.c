/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:18:58 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/07 22:44:03 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	make_map(t_game *game, int fd)
{
	char	*line;

	while (1)
	{
		line = gnl_cub(fd);
		if (!line)
			_error(MAP_ERR);
		if (!is_empty_str(line))
			break ;
		ft_free(line);
	}
	game->map.map = ft_malloc(sizeof(char *));
	if (!game->map.map)
		_error(MALLOC_ERR);
	game->map.map[0] = 0;
	while (1)
	{
		if (!line)
			break ;
		put_map(game, line);
		line = gnl_cub(fd);
	}
	remove_empty(game);
}

void	put_map(t_game *game, char *line)
{
	int		i;
	char	**res;

	i = 0;
	while (game->map.map[i])
		i++;
	res = ft_malloc(sizeof(char *) * (i + 2));
	if (!res)
		_error(MALLOC_ERR);
	i = 0;
	while (game->map.map[i])
	{
		res[i] = game->map.map[i];
		i++;
	}
	res[i++] = line;
	res[i] = 0;
	ft_free(game->map.map);
	game->map.map = res;
}

void	remove_empty(t_game *game)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	while (game->map.map[i])
		i++;
	while (is_empty_str(game->map.map[i - 1]))
	{
		res = ft_malloc(sizeof(char *) * i);
		if (!res)
			_error(MALLOC_ERR);
		j = 0;
		while (j < i - 1)
		{
			res[j] = game->map.map[j];
			j++;
		}
		res[j] = 0;
		ft_free(game->map.map[j]);
		ft_free(game->map.map);
		game->map.map = res;
		i--;
	}
}
