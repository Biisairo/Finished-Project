/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:22:54 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/06 10:57:00 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	update_mouse(t_game *game)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(game->win, &mouse_x, &mouse_y);
	game->pos.rotate = (mouse_x - SCREEN_WIDTH / 2) * ROTATE_SPEED;
	mlx_mouse_move(game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

int	key_release(int key, void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (game->keydown != key)
		return (0);
	game->keydown = -1;
	game->pos.dx = 0;
	game->pos.dy = 0;
	return (0);
}

int	is_empty(t_game *game, int x, int y)
{
	return (game->map.map[y][x] == '0'
		|| game->map.map[y][x] == 'N' || game->map.map[y][x] == 'S'
		|| game->map.map[y][x] == 'W' || game->map.map[y][x] == 'E'
		|| game->map.map[y][x] == 'v' || game->map.map[y][x] == 'h');
}

void	update_pos(t_game *game)
{
	if (game->keydown == KEY_W)
		key_w(game);
	else if (game->keydown == KEY_S)
		key_s(game);
	else if (game->keydown == KEY_A)
		key_a(game);
	else if (game->keydown == KEY_D)
		key_d(game);
	if (is_empty(game, (int)game->pos.x, (int)(game->pos.y + game->pos.dy * 2)))
		game->pos.y += game->pos.dy;
	if (is_empty(game, (int)(game->pos.x + game->pos.dx * 2), (int)game->pos.y))
		game->pos.x += game->pos.dx;
}

int	game_loop(void *game_ptr)
{
	t_game	*game;
	double	old_dir_x;

	game = (t_game *)game_ptr;
	update_pos(game);
	update_mouse(game);
	update_doors(game);
	old_dir_x = game->pos.dir_x;
	game->pos.dir_x = game->pos.dir_x * cos(game->pos.rotate)
		- game->pos.dir_y * sin(game->pos.rotate);
	game->pos.dir_y = old_dir_x * sin(game->pos.rotate)
		+ game->pos.dir_y * cos(game->pos.rotate);
	old_dir_x = game->pos.plane_x;
	game->pos.plane_x = game->pos.plane_x * cos(game->pos.rotate)
		- game->pos.plane_y * sin(game->pos.rotate);
	game->pos.plane_y = old_dir_x * sin(game->pos.rotate)
		+ game->pos.plane_y * cos(game->pos.rotate);
	ray_cast(game);
	draw_minimap(game);
	return (0);
}
