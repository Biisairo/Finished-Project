/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:46:32 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 12:07:13 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_av(t_game *game, int fd)
{
	char	*line;
	int		ck[6];
	int		is_full;
	int		i;

	ft_bzero(ck, sizeof(int) * 6);
	while (1)
	{
		line = gnl_cub(fd);
		if (!line)
			_error(MAP_ERR);
		check_seq(game, line, ck);
		ft_free(line);
		i = 0;
		is_full = 0;
		while (i < 6)
		{
			if (ck[i] == 1)
				is_full += 1;
			i++;
		}
		if (is_full == 6)
			break ;
	}
}

t_img	load_img(t_game *game, char *path)
{
	t_img	res;

	res.img = mlx_xpm_file_to_image(game->mlx, path,
			&res.img_width,
			&res.img_height);
	if (!res.img)
		_error(NOFILE_ERR);
	res.img_ptr = mlx_get_data_addr(res.img, &res.bit_per_pixel,
			&res.size_line, &res.endian);
	return (res);
}

t_floor	load_color(char **color)
{
	t_floor	res;

	res.r = atoi_cub(color[0]);
	res.g = atoi_cub(color[1]);
	res.b = atoi_cub(color[2]);
	res.color = res.r << 16 | res.g << 8 | res.b;
	return (res);
}
