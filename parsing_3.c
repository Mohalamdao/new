/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:43 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:45:44 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir_plane_ns(t_cub3d *cub, int south)
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

void	set_dir_plane_ew(t_cub3d *cub, int west)
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
