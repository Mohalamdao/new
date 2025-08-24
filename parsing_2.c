/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:08 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 22:50:49 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_path_text(char *str)
{
	if (!str || !*str)
		return (1);
	if (access(str, F_OK) == -1)
		return (1);
	return (0);
}

int	validate_rgb_part(char *p)
{
	int	j;
	int	val;

	if (!p)
		return (1);
	j = 0;
	while (p[j] == ' ')
		j++;
	if (p[j] == '\0')
		return (1);
	while (p[j])
	{
		if (p[j] < '0' || p[j] > '9')
			return (1);
		j++;
	}
	val = ft_atoi(p);
	if (val < 0 || val > 255)
		return (1);
	return (0);
}

int	count_parts(char **rgb)
{
	int	i;

	if (!rgb)
		return (0);
	i = 0;
	while (rgb[i])
		i++;
	return (i);
}

int	check_rgb(char *str, int i, int j)
{
	char	**rgb;
	int		ret;

	(void)i;
	(void)j;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (1);
	if (count_parts(rgb) != 3)
	{
		free_split(rgb);
		return (1);
	}
	ret = 0;
	i = 0;
	while (rgb[i])
	{
		if (validate_rgb_part(rgb[i]))
		{
			ret = 1;
			break ;
		}
		i++;
	}
	return (free_split(rgb), ret);
}

int	check_rgb_text(t_cub3d cub)
{
	if (check_path_text(cub.no_text) == 1)
		return (1);
	if (check_path_text(cub.so_text) == 1)
		return (1);
	if (check_path_text(cub.we_text) == 1)
		return (1);
	if (check_path_text(cub.ea_text) == 1)
		return (1);
	if (check_rgb(cub.ceiling, 0, 0) == 1)
		return (1);
	if (check_rgb(cub.floor, 0, 0) == 1)
		return (1);
	return (0);
}
