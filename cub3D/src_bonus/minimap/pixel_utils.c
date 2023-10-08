/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:05:08 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 11:43:40 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	pixel_put(t_map_img *mini, int x, int y, int color)
{
	char	*dst;

	dst = mini->addr + (y * mini->line_length + x * (mini->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	pixel_get(t_map_img *mini, int x, int y)
{
	char	*dst;

	dst = mini->addr + (y * mini->line_length + x * (mini->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
