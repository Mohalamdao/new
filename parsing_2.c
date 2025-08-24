/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:20:00 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 20:19:40 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_path_text(char *str)
{
	if (access(str, F_OK) == -1)
		return (1);
	return (0);
}

static int	validate_rgb_part(char *p)
{
	int	j;

	j = 0;
	while (p[j] == ' ')
		j++;
	while (p[j])
	{
		if (p[j] < '0' || p[j] > '9')
			return (1);
		j++;
	}
	if (ft_atoi(p) > 255 || ft_atoi(p) < 0)
		return (1);
	return (0);
}

static int	count_parts(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		i++;
	return (i);
}

int	check_rgb(char *str, int i, int j)
{
	char	**rgb;

	(void)i;
	(void)j;
	rgb = ft_split(str, ',');
	if (!rgb)
		return (1);
	if (count_parts(rgb) != 3)
		return (1);
	i = 0;
	while (rgb[i])
	{
		if (validate_rgb_part(rgb[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_rgb_text(t_cub3d cub)
{
	if (check_path_text(cub.ea_text) == 1)
		return (1);
	if (check_path_text(cub.no_text) == 1)
		return (1);
	if (check_path_text(cub.ea_text) == 1)
		return (1);
	if (check_path_text(cub.so_text) == 1)
		return (1);
	if (check_rgb(cub.ceiling, 0, 0) == 1)
		return (1);
	if (check_rgb(cub.floor, 0, 0) == 1)
		return (1);
	return (0);
}

static void	set_dir_plane_ns(t_cub3d *cub, int south)
{
	if (south)
	{
		cub->dir_x = 0;
		cub->dir_y = 1;
		cub->plane_x = -0.66;
		cub->plane_y = 0;
		return ;
	}
	cub->dir_x = 0;
	cub->dir_y = -1;
	cub->plane_x = 0.66;
	cub->plane_y = 0;
}

static void	set_dir_plane_ew(t_cub3d *cub, int west)
{
	if (west)
	{
		cub->dir_x = -1;
		cub->dir_y = 0;
		cub->plane_x = 0;
		cub->plane_y = -0.66;
		return ;
	}
	cub->dir_x = 1;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66;
}

void	init_player_direction(t_cub3d *cub)
{
	cub->pos_x = cub->pos_j_player + 0.5;
	cub->pos_y = cub->pos_i_player + 0.5;
	if (cub->orientation == 'N')
	{
		set_dir_plane_ns(cub, 0);
		return ;
	}
	if (cub->orientation == 'S')
	{
		set_dir_plane_ns(cub, 1);
		return ;
	}
	if (cub->orientation == 'E')
	{
		set_dir_plane_ew(cub, 0);
		return ;
	}
	if (cub->orientation == 'W')
		set_dir_plane_ew(cub, 1);
}
