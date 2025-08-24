/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:59:59 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 19:50:13 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_wall_textures(t_cub3d *cub)
{
	int	width;
	int	height;

	if (!cub || !cub->mlx_ptr)
		return ;
	if (cub->no_text)
		cub->no_wall = mlx_xpm_file_to_image(cub->mlx_ptr,
				cub->no_text, &width, &height);
	if (cub->so_text)
		cub->so_wall = mlx_xpm_file_to_image(cub->mlx_ptr,
				cub->so_text, &width, &height);
}

void	load_remaining_textures(t_cub3d *cub)
{
	int	width;
	int	height;

	if (!cub || !cub->mlx_ptr)
		return ;
	if (cub->ea_text)
		cub->ea_wall = mlx_xpm_file_to_image(cub->mlx_ptr,
				cub->ea_text, &width, &height);
	if (cub->we_text)
		cub->we_wall = mlx_xpm_file_to_image(cub->mlx_ptr,
				cub->we_text, &width, &height);
}

int	get_wall_orientation(double ray_dir_x, double ray_dir_y,
		double hit_x, double hit_y)
{
	(void)hit_x;
	(void)hit_y;
	if (ray_dir_x > 0 && ray_dir_x > fabs(ray_dir_y))
		return (1);
	if (ray_dir_x < 0 && (-ray_dir_x) > fabs(ray_dir_y))
		return (3);
	if (ray_dir_y > 0)
		return (2);
	return (0);
}

void	*get_texture_image(t_cub3d *cub, int orientation)
{
	if (!cub)
		return (NULL);
	if (orientation == 0 && cub->no_wall)
		return (cub->no_wall);
	if (orientation == 1 && cub->ea_wall)
		return (cub->ea_wall);
	if (orientation == 2 && cub->so_wall)
		return (cub->so_wall);
	if (orientation == 3 && cub->we_wall)
		return (cub->we_wall);
	return (NULL);
}
