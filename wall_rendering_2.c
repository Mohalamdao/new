/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:46:17 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:46:18 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_pixel_ctx(t_cub3d *cub, t_wall_ctx *c, t_wvars *v)
{
	int		color;
	void	*tex;

	tex = get_texture_image(cub, c->orientation);
	if (tex)
		color = read_pixel_from_texture(tex, v->tex_x, v->tex_y);
	else
		color = get_texture_color(cub, c->orientation);
	put_pixel_to_image(&c->img, c->x, v->y0, color);
}

void	draw_wall_column_textured(t_cub3d *cub, t_wall_ctx *c)
{
	t_wvars	v;

	setup_strip_bounds(c, &v);
	draw_flat_top(c, v.y0);
	prepare_tex_coords(cub, c, &v);
	while (v.y0 <= v.y1)
	{
		v.tex_y = (int)v.tex_pos;
		if (v.tex_y < 0)
			v.tex_y = 0;
		if (v.tex_y >= v.tex_h)
			v.tex_y = v.tex_h - 1;
		draw_wall_pixel_ctx(cub, c, &v);
		v.tex_pos += v.step;
		v.y0++;
	}
	draw_flat_bottom(c, v.y1);
}
