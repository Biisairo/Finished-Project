/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:58:54 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/06 11:45:48 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_game(t_game *game)
{
	(void)game;
	ft_clear();
	exit(0);
	return (0);
}

void	_error(int err)
{
	if (err == MALLOC_ERR)
		printf("Memory not allocated\n");
	else if (err == MAP_ERR)
		printf("Error\n");
	else if (err == FILE_ERR)
		printf("Can't open file\n");
	else if (err == NOFILE_ERR)
		printf("File not exist\n");
	else if (err == MLX_ERR)
		printf("minilibx doesn't work\n");
	ft_clear();
	exit(1);
}
