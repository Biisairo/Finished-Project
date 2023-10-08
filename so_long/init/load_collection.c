/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_collection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:11:21 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/09 15:21:00 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_collection(t_game *game)
{
	game->collection.img = mlx_xpm_file_to_image(game->mlx,
			"./assets/others/collection.xpm", &(game->collection.img_width),
			&(game->collection.img_height));
	if (!(game->collection.img))
		ft_error(2, game);
}
