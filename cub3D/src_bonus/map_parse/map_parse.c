/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:30:08 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/07 16:16:50 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	map_parse(t_game *game, int ac, char **av)
{
	int	fd;

	ft_bzero((void *)&(game->map), sizeof(t_map));
	ft_bzero((void *)&(game->pos), sizeof(t_pos));
	game->keydown = -1;
	fd = get_fd(ac, av);
	load_av(game, fd);
	make_map(game, fd);
	close(fd);
	check_map(game);
	make_map_img(game);
	minimap_init(game);
}

void	minimap_init(t_game *game)
{
	game->minimap.img = mlx_new_image(game->mlx, 180, 120);
	if (!game->minimap.img)
		_error(MLX_ERR);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bits_per_pixel,
			&game->minimap.line_length,
			&game->minimap.endian);
}

int	get_fd(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		_error(MAP_ERR);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		_error(FILE_ERR);
	check_path(av[1]);
	return (fd);
}

void	check_path(char *str)
{
	if (ft_strncmp(".cub", &str[ft_strlen(str) - 4], 4))
		_error(MAP_ERR);
	return ;
}
