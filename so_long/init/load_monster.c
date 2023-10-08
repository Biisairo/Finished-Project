/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:03 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/10 10:42:39 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	load_monster(t_game *game)
{
	t_monster	*p;
	size_t		i;

	init_monster(game);
	if (!(game->monster_cnt))
		return ;
	i = 0;
	p = game->monster;
	while (i < game->monster_cnt)
	{
		load_monster_img(game, p + i);
		i++;
	}
}

void	load_monster_img(t_game *game, t_monster *p)
{
	char	file[30];
	char	*c;
	int		i;

	i = 0;
	while (++i < 9)
	{
		file[0] = 0;
		c = ft_itoa(i);
		if (!c)
			ft_error(0, game);
		ft_strlcat(file, "./assets/monster/monster", 30);
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

size_t	count_monster(t_game *game)
{
	size_t	x;
	size_t	y;
	size_t	cnt;

	cnt = 0;
	x = 0;
	while (x < game->map->height)
	{
		y = 0;
		while (y < game->map->width)
		{
			if ((game->map->map)[x][y] == 'M')
				cnt++;
			y++;
		}
		x++;
	}
	return (cnt);
}

void	pos_monster(t_game *game)
{
	size_t	x;
	size_t	y;
	size_t	cnt;

	cnt = 0;
	x = 0;
	while (x < game->map->height)
	{
		y = 0;
		while (y < game->map->width)
		{
			if ((game->map->map)[x][y] == 'M')
			{
				((game->monster)[cnt].pos)[0] = y * 32;
				((game->monster)[cnt].pos)[1] = x * 32;
				cnt++;
				(game->monster)[cnt].direction_state = (size_t)(game->monster)
					% 2;
			}
			y++;
		}
		x++;
	}
}

void	init_monster(t_game *game)
{
	game->monster_cnt = count_monster(game);
	if (game->monster_cnt == 0)
		return ;
	game->monster = ft_malloc(sizeof(t_monster) * game->monster_cnt);
	if (!(game->monster))
		ft_error(0, game);
	pos_monster(game);
}
