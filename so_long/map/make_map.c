/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:47:07 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/12 08:58:46 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	make_map(t_map *map, char *map_name)
{
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		if (re_map(map))
		{
			ft_free(line);
			return (1);
		}
		if (del_linefeed(&line))
		{
			ft_free(line);
			return (1);
		}
		(map->map)[map->height] = line;
		map->height += 1;
	}
	return (0);
}

int	del_linefeed(char **line)
{
	size_t	len;
	size_t	i;
	char	*tmp;

	len = ft_strlen(*line);
	tmp = ft_malloc(sizeof(char) * len);
	if (!tmp)
		return (1);
	i = 0;
	while (i < len)
	{
		tmp[i] = (*line)[i];
		i++;
	}
	tmp[i - 1] = 0;
	ft_free(*line);
	*line = tmp;
	return (0);
}

int	re_map(t_map *map)
{
	char	**tmp;
	size_t	i;

	tmp = ft_malloc(sizeof(char *) * map->height + 1);
	if (!tmp)
		return (1);
	i = 0;
	if (map->map)
	{
		while (i < (map->height))
		{
			tmp[i] = (map->map)[i];
			i++;
		}
		ft_free(map->map);
	}
	tmp[i] = 0;
	map->map = tmp;
	return (0);
}
