/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:03 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/09 16:34:22 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_map(t_game *game)
{
	t_map	*p;

	p = game->map;
	p->img[0].img = mlx_xpm_file_to_image(game->mlx, "./assets/others/wall.xpm",
			&(p->img[0].img_width), &(p->img[0].img_height));
	if (!p->img[0].img)
		ft_error(2, game);
	p->img[1].img = mlx_xpm_file_to_image(game->mlx,
			"./assets/others/background.xpm", &(p->img[1].img_width),
			&(p->img[1].img_height));
	if (!p->img[1].img)
		ft_error(2, game);
	p->img[2].img = mlx_xpm_file_to_image(game->mlx,
			"./assets/others/gate_close.xpm", &(p->img[1].img_width),
			&(p->img[1].img_height));
	if (!p->img[1].img)
		ft_error(2, game);
	p->img[3].img = mlx_xpm_file_to_image(game->mlx,
			"./assets/others/gate_open.xpm", &(p->img[1].img_width),
			&(p->img[1].img_height));
	if (!p->img[1].img)
		ft_error(2, game);
}
