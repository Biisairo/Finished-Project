/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:24:46 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/07 15:58:40 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	load_gun_img(t_game *game)
{
	game->pos.gun.gun_img[0] = load_img(game, "./asset/gun/gun0.xpm");
	game->pos.gun.gun_img[1] = load_img(game, "./asset/gun/gun1.xpm");
	game->pos.gun.gun_img[2] = load_img(game, "./asset/gun/gun2.xpm");
	game->pos.gun.gun_img[3] = load_img(game, "./asset/gun/gun3.xpm");
	game->pos.gun.gun_img[4] = load_img(game, "./asset/gun/gun4.xpm");
	game->pos.gun.img_order = 0;
}

void	key_v(t_game *game)
{
	if (game->pos.gun.img_order == 0)
		game->pos.gun.img_order += SHOT_SPEED;
}

void	update_gun_pos(t_game *game)
{
	if (game->pos.gun.img_order > 0)
		game->pos.gun.img_order += SHOT_SPEED;
	if (game->pos.gun.img_order >= 5)
		game->pos.gun.img_order = 0;
}

void	draw_gun(t_game *game, t_img *img)
{
	t_img	gun_img;
	int		gun_x;
	int		gun_y;

	gun_img = game->pos.gun.gun_img[(int)game->pos.gun.img_order];
	gun_y = 0;
	while (gun_y < gun_img.img_height * GUN_SIZE)
	{
		gun_x = 0;
		while (gun_x < gun_img.img_width * GUN_SIZE)
		{
			set_color(img, GUN_X + gun_x, GUN_Y + gun_y,
				get_color(&gun_img, gun_x / GUN_SIZE, gun_y / GUN_SIZE));
			gun_x++;
		}
		gun_y++;
	}
	update_gun_pos(game);
}
