/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:36:36 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/12 08:59:05 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
** -1 : mlx, win error
** 0 : null guard
** 1 : map error
** 2 : img file not exist
*/

void	ft_error(int error_no, t_game *game)
{
	if (error_no == -1)
		ft_printf("MLX NOT WORKING\n");
	else if (error_no == 0)
		ft_printf("Null Guard\n");
	else if (error_no == 11)
		ft_printf("Error\nThe map file not exist\n");
	else if (error_no == 12)
		ft_printf("Error\nThe map is too small\n");
	else if (error_no == 13)
	{
		ft_printf("Error\nThe map must contain 1 exit,");
		ft_printf(" at least 1 collectible, and 1 starting position\n");
	}
	else if (error_no == 14)
		ft_printf("Error\nThe map must be closed/surrounded by walls\n");
	else if (error_no == 15)
		ft_printf("Error\nThe map has wrong arguments");
	else if (error_no == 2)
		ft_printf("File not open\n");
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	ft_clear();
	exit(1);
}
