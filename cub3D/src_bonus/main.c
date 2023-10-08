/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:20:37 by heejikim          #+#    #+#             */
/*   Updated: 2023/02/07 17:04:38 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	calc_dir_2(t_game *game)
{
	if (game->map.dir == 'W')
	{
		game->pos.dir_x = -1;
		game->pos.dir_y = 0;
		game->pos.plane_x = 0;
		game->pos.plane_y = -0.66;
	}
	else if (game->map.dir == 'E')
	{
		game->pos.dir_x = 1;
		game->pos.dir_y = 0;
		game->pos.plane_x = 0;
		game->pos.plane_y = 0.66;
	}
}

void	calc_dir(t_game *game)
{
	if (game->map.dir == 'N')
	{
		game->pos.dir_x = 0;
		game->pos.dir_y = -1;
		game->pos.plane_x = 0.66;
		game->pos.plane_y = 0;
	}
	else if (game->map.dir == 'S')
	{
		game->pos.dir_x = 0;
		game->pos.dir_y = 1;
		game->pos.plane_x = -0.66;
		game->pos.plane_y = 0;
	}
	else
		calc_dir_2(game);
}

int	main(int ac, char **av)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		_error(MLX_ERR);
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game.win)
		_error(MLX_ERR);
	map_parse(&game, ac, av);
	calc_dir(&game);
	load_gun_img(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, key_release, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, exit_game, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_mouse_move(game.win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_mouse_hide(game.mlx, game.win);
	mlx_loop(game.mlx);
	return (0);
}
