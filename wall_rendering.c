/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:46:22 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:46:23 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_pixel_from_texture(void *img, int tx, int ty)
{
	t_tex	t;
	char	*px;

	if (!img)
		return (0);
	t.data = mlx_get_data_addr(img, &t.bpp, &t.ll, &t.endian);
	if (!t.data || t.bpp <= 0)
		return (0);
	px = t.data + ty * t.ll + tx * (t.bpp / 8);
	return (*(int *)px);
}

void	draw_flat_top(t_wall_ctx *c, int y0)
{
	int	y;

	y = 0;
	while (y < y0)
	{
		put_pixel_to_image(&c->img, c->x, y, c->ceiling_color);
		y++;
	}
}

void	draw_flat_bottom(t_wall_ctx *c, int y1)
{
	int	y;

	y = y1 + 1;
	while (y < c->height)
	{
		put_pixel_to_image(&c->img, c->x, y, c->floor_color);
		y++;
	}
}

void	setup_strip_bounds(t_wall_ctx *c, t_wvars *v)
{
	if (c->wall_dist < 0.05)
		c->wall_dist = 0.05;
	v->line_h = (int)((double)c->height / c->wall_dist);
	if (v->line_h < 1)
		v->line_h = 1;
	v->y0 = -v->line_h / 2 + c->height / 2;
	v->y1 = v->line_h / 2 + c->height / 2;
	if (v->y0 < 0)
		v->y0 = 0;
	if (v->y1 >= c->height)
		v->y1 = c->height - 1;
}

void	prepare_tex_coords(t_cub3d *cub, t_wall_ctx *c, t_wvars *v)
{
	v->tex_w = 64;
	v->tex_h = 64;
	v->tex_x = (int)(cub->wall_x * (double)v->tex_w);
	if (v->tex_x < 0)
		v->tex_x = 0;
	if (v->tex_x >= v->tex_w)
		v->tex_x = v->tex_w - 1;
	if (c->orientation == 0 || c->orientation == 3)
		v->tex_x = v->tex_w - 1 - v->tex_x;
	v->step = (double)v->tex_h / (double)v->line_h;
	v->tex_pos = (double)(v->y0 - (-v->line_h / 2 + c->height / 2)) * v->step;
}
