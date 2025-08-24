/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:46:03 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:46:04 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_data(void *texture_img, int *line_length)
{
	int	bpp;
	int	endian;

	if (!texture_img || !line_length)
		return (NULL);
	return (mlx_get_data_addr(texture_img, &bpp, line_length, &endian));
}

void	secure_texture_coords(int *tex_x, int *tex_y)
{
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= 64)
		*tex_x = 63;
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= 64)
		*tex_y = 63;
}

int	read_texture_pixel(char *texture_data, int tex_x,
		int tex_y, int line_length)
{
	char	*pixel;

	if (!texture_data || line_length <= 0)
		return (0xFF0000);
	if (tex_x < 0 || tex_x >= 64 || tex_y < 0 || tex_y >= 64)
		return (0xFF0000);
	pixel = texture_data + (tex_y * line_length + tex_x * 4);
	return (*(int *)pixel);
}

int	get_texture_pixel(t_cub3d *cub, int orientation, int tex_x, int tex_y)
{
	void	*texture_img;
	char	*texture_data;
	int		line_length;

	if (!cub)
		return (get_texture_color(cub, orientation));
	texture_img = get_texture_image(cub, orientation);
	if (!texture_img)
		return (get_texture_color(cub, orientation));
	texture_data = get_texture_data(texture_img, &line_length);
	if (!texture_data)
		return (get_texture_color(cub, orientation));
	secure_texture_coords(&tex_x, &tex_y);
	return (read_texture_pixel(texture_data, tex_x, tex_y, line_length));
}

int	get_texture_color(t_cub3d *cub, int orientation)
{
	(void)cub;
	if (orientation == 0)
		return (0xFF0000);
	if (orientation == 1)
		return (0x00FF00);
	if (orientation == 2)
		return (0x0000FF);
	return (0xFFFF00);
}
