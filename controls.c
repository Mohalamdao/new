/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:42:00 by molamdao          #+#    #+#             */
/*   Updated: 2025/08/24 19:35:21 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	update_position(t_cub3d *cub, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_y >= 0 && map_y < cub->height
		&& map_x >= 0 && map_x < cub->width)
	{
		if (cub->map[map_y] && cub->map[map_y][map_x] != '1')
		{
			cub->pos_x = new_x;
			cub->pos_y = new_y;
		}
	}
}

void	move_player_forward_back(t_cub3d *cub, int forward)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	if (forward)
	{
		new_x = cub->pos_x + cub->dir_x * move_speed;
		new_y = cub->pos_y + cub->dir_y * move_speed;
	}
	else
	{
		new_x = cub->pos_x - cub->dir_x * move_speed;
		new_y = cub->pos_y - cub->dir_y * move_speed;
	}
	update_position(cub, new_x, new_y);
}

void	move_player_strafe(t_cub3d *cub, int right)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	if (right)
	{
		new_x = cub->pos_x + cub->plane_x * move_speed;
		new_y = cub->pos_y + cub->plane_y * move_speed;
	}
	else
	{
		new_x = cub->pos_x - cub->plane_x * move_speed;
		new_y = cub->pos_y - cub->plane_y * move_speed;
	}
	update_position(cub, new_x, new_y);
}

static void	rotate_left(t_cub3d *cub, double rot_speed,
		double old_dir_x, double old_plane_x)
{
	cub->dir_x = cub->dir_x * cos(rot_speed)
		- cub->dir_y * sin(rot_speed);
	cub->dir_y = old_dir_x * sin(rot_speed)
		+ cub->dir_y * cos(rot_speed);
	cub->plane_x = cub->plane_x * cos(rot_speed)
		- cub->plane_y * sin(rot_speed);
	cub->plane_y = old_plane_x * sin(rot_speed)
		+ cub->plane_y * cos(rot_speed);
}

static void	rotate_right(t_cub3d *cub, double rot_speed,
		double old_dir_x, double old_plane_x)
{
	cub->dir_x = cub->dir_x * cos(-rot_speed)
		- cub->dir_y * sin(-rot_speed);
	cub->dir_y = old_dir_x * sin(-rot_speed)
		+ cub->dir_y * cos(-rot_speed);
	cub->plane_x = cub->plane_x * cos(-rot_speed)
		- cub->plane_y * sin(-rot_speed);
	cub->plane_y = old_plane_x * sin(-rot_speed)
		+ cub->plane_y * cos(-rot_speed);
}

void	rotate_camera(t_cub3d *cub, int left)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.05;
	old_dir_x = cub->dir_x;
	old_plane_x = cub->plane_x;
	if (left)
		rotate_left(cub, rot_speed, old_dir_x, old_plane_x);
	else
		rotate_right(cub, rot_speed, old_dir_x, old_plane_x);
}



