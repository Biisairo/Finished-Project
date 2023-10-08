/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_av_asset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:46:32 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/06 09:08:30 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_seq(t_game *game, char *line, int ck[7])
{
	int	flag;

	flag = 0;
	flag += check_direction(game, line, ck);
	flag += check_floor(game, line, ck);
	flag += check_door(game, line, ck);
	if (flag == 3)
		_error(MAP_ERR);
}

int	check_direction(t_game *game, char *line, int ck[7])
{
	int		flag;
	char	*path;

	flag = 0;
	if (ft_strncmp(line + find_index_cub(line), "NO ", 3) == 0)
		flag = 0;
	else if (ft_strncmp(line + find_index_cub(line), "SO ", 3) == 0)
		flag = 1;
	else if (ft_strncmp(line + find_index_cub(line), "WE ", 3) == 0)
		flag = 2;
	else if (ft_strncmp(line + find_index_cub(line), "EA ", 3) == 0)
		flag = 3;
	else if (*(line + find_index_cub(line)) == 0)
		return (0);
	else
		return (1);
	if (ck[flag])
		_error(MAP_ERR);
	else
		ck[flag] += 1;
	path = line + find_index_cub(line + find_index_cub(line) + 2)
		+ find_index_cub(line) + 2;
	game->map.wall[flag] = load_img(game, path);
	return (0);
}

int	check_door(t_game *game, char *line, int ck[7])
{
	char	*path;

	if (*(line + find_index_cub(line)) == 0)
		return (0);
	else if (ft_strncmp(line + find_index_cub(line), "DOOR ", 5) != 0)
		return (1);
	if (ck[6])
		_error(MAP_ERR);
	ck[6] += 1;
	path = line + find_index_cub(line + find_index_cub(line) + 4)
		+ find_index_cub(line) + 4;
	game->map.door_img = load_img(game, path);
	return (0);
}

int	check_floor(t_game *game, char *line, int ck[7])
{
	int		flag;
	char	**color;

	flag = 0;
	if (ft_strncmp(line + find_index_cub(line), "F ", 2) == 0)
		flag = 0;
	else if (ft_strncmp(line + find_index_cub(line), "C ", 2) == 0)
		flag = 1;
	else if (*(line + find_index_cub(line)) == 0)
		return (0);
	else
		return (1);
	if (ck[flag + 4])
		_error(MAP_ERR);
	else
		ck[flag + 4] += 1;
	color = ft_split(line + find_index_cub(line) + 1, ',');
	if (!color)
		_error(MALLOC_ERR);
	trim_color(color);
	if (!is_three(color) || !str_digit(color))
		_error(MAP_ERR);
	game->map.floor[flag] = load_color(color);
	free_color(color);
	return (0);
}
