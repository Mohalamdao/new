/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:54 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:45:55 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	cast_single_ray_with_orientation(t_cub3d *cub, t_ray_params *p)
{
	t_ray	r;
	double	d;

	init_dda_pos_delta(&r, p);
	init_dda_steps(&r, p);
	perform_dda(cub, &r);
	d = calc_perp_dist(cub, &r, p);
	*(p->orientation) = get_wall_orientation_dda(r.side, r.step_x, r.step_y);
	return (d);
}

void	render_column(t_cub3d *cub, t_render_ctx *ctx, int x)
{
	t_ray_params	p;
	t_wall_ctx		w;
	int				o;
	double			d;

	p.pos_x = cub->pos_x;
	p.pos_y = cub->pos_y;
	p.ray_dir_x = cub->dir_x
		+ cub->plane_x * (2 * x / (double)ctx->width - 1);
	p.ray_dir_y = cub->dir_y
		+ cub->plane_y * (2 * x / (double)ctx->width - 1);
	p.orientation = &o;
	d = cast_single_ray_with_orientation(cub, &p);
	w.img.data = ctx->img_data;
	w.img.ll = ctx->line_length;
	w.width = ctx->width;
	w.height = ctx->height;
	w.floor_color = ctx->floor_color;
	w.ceiling_color = ctx->ceiling_color;
	w.wall_dist = d;
	w.x = x;
	w.orientation = o;
	draw_wall_column_textured(cub, &w);
}

void	render_3d_view(t_cub3d *cub, t_render_ctx *ctx)
{
	int	x;

	x = 0;
	while (x < ctx->width)
	{
		render_column(cub, ctx, x);
		x++;
	}
}
