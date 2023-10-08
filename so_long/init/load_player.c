/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:03 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 12:31:23 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_player(t_game *game)
{
	t_player	*p;
	char		file[30];
	char		*c;
	int			i;

	i = 0;
	p = &(game->player);
	while (++i < 53)
	{
		file[0] = 0;
		c = ft_itoa(i);
		if (!c)
			ft_error(0, game);
		ft_strlcat(file, "./assets/player/player", 30);
		ft_strlcat(file, c, 30);
		ft_free(c);
		ft_strlcat(file, ".xpm", 30);
		p->img[i - 1].img = mlx_xpm_file_to_image(game->mlx, file, &(p->img[i
					- 1].img_width), &(p->img[i - 1].img_height));
		if (!p->img[i - 1].img)
			ft_error(2, game);
		init_player(game);
	}
}

void	init_player(t_game *game)
{
	t_player	*p;

	p = &(game->player);
	p->direction_state = 0;
	p->jump_state = 0;
	p->move_state = 0;
	p->drop_state = 0;
	p->down_state = 0;
	p->life = 1;
	p->pos[0] = (game->map->start_pos)[1] * 32;
	p->pos[1] = (game->map->start_pos)[0] * 32;
}
