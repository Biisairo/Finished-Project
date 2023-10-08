/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:11:29 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/12 09:00:36 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_printf("Put a map file\n");
		exit(1);
	}
	init_game(&game, av[1]);
	mlx_hook(game.win, 02, 0, key_press, &game);
	mlx_hook(game.win, 03, 0, key_release, &game);
	mlx_hook(game.win, 17, 0, exit_mlx, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	return (0);
}
