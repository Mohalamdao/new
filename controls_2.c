/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:44:25 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:44:26 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
