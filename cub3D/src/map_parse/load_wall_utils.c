/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:17:57 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 10:28:50 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_color(char **color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		ft_free(color[i]);
		i++;
	}
	ft_free(color);
}

void	trim_color(char **color)
{
	int		i;
	char	*tmp;

	i = 0;
	while (color[i])
	{
		tmp = ft_strtrim(color[i], " \t\n\v\f\r");
		if (!tmp)
			_error(MALLOC_ERR);
		ft_free(color[i]);
		color[i] = tmp;
		i++;
	}
}

int	find_index_cub(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_is_whitespace(s[i]))
			break ;
		i++;
	}
	if (!s[i])
		return (0);
	return (i);
}
