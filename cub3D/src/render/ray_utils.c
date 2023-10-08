/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:51:37 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/07 17:04:40 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_color(t_img *img, int col, int row)
{
	char	*dst;

	dst = img->img_ptr + (row * img->size_line + col * img->bit_per_pixel / 8);
	return (*(int *)dst);
}

void	set_color(t_img	*img, int col, int row, int color)
{
	char	*dst;

	dst = img->img_ptr + (row * img->size_line + col * img->bit_per_pixel / 8);
	*(int *)dst = color;
}

double	ft_absd(double n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

t_img	create_img(t_game *game)
{
	t_img	res;

	res.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!res.img)
		_error(MLX_ERR);
	res.img_width = SCREEN_WIDTH;
	res.img_height = SCREEN_HEIGHT;
	res.img_ptr = mlx_get_data_addr(res.img, &res.bit_per_pixel,
			&res.size_line, &res.endian);
	return (res);
}

int	ft_dir(double d)
{
	if (d > 0)
		return (1);
	if (d < 0)
		return (-1);
	return (0);
}
