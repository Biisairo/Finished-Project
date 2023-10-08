/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_cub3D.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:32:46 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/05 11:42:58 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*gnl_cub(int fd)
{
	char	*line;
	char	*res;
	int		i;

	line = get_next_line(fd);
	if (!line)
		return (0);
	res = ft_malloc(sizeof(char) * ft_strlen(line));
	if (!res)
		_error(MALLOC_ERR);
	i = 0;
	while (line[i])
	{
		res[i] = line[i];
		i++;
	}
	i--;
	res[i] = 0;
	ft_free(line);
	return (res);
}
