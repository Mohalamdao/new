/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:30:00 by molamdao          #+#    #+#             */
/*   Updated: 2025/08/24 20:01:00 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static int	get_wall_orientation_dda(int side, int step_x, int step_y)
{
	if (side == 0)
	{
		if (step_x > 0)
			return (0);
		return (2);
	}
	if (step_y > 0)
		return (3);
	return (1);
}

static void	init_dda_pos_delta(t_ray *r, t_ray_params *p)
{
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	if (p->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / p->ray_dir_x);
	if (p->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / p->ray_dir_y);
}

static void	init_dda_steps(t_ray *r, t_ray_params *p)
{
	if (p->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	}
	if (p->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	}
}

static void	perform_dda(t_cub3d *cub, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_y < 0 || r->map_y >= cub->height
			|| r->map_x < 0 || r->map_x >= cub->width)
			break ;
		if (cub->map[r->map_y] && r->map_x < (int)strlen(cub->map[r->map_y])
			&& cub->map[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

static double	calc_perp_dist(t_cub3d *cub, t_ray *r, t_ray_params *p)
{
	double	d;
	double	hx;
	double	hy;

	if (r->side == 0)
		d = (r->map_x - p->pos_x + (1 - r->step_x) / 2) / p->ray_dir_x;
	else
		d = (r->map_y - p->pos_y + (1 - r->step_y) / 2) / p->ray_dir_y;
	hx = p->pos_x + d * p->ray_dir_x;
	hy = p->pos_y + d * p->ray_dir_y;
	if (r->side == 0)
		cub->wall_x = hy;
	else
		cub->wall_x = hx;
	cub->wall_x -= floor(cub->wall_x);
	if (cub->wall_x < 0)
		cub->wall_x = 0;
	if (cub->wall_x >= 1.0)
		cub->wall_x = 0.999999;
	if (d < 0.01)
		d = 0.01;
	return (d);
}

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

static void	render_column(t_cub3d *cub, t_render_ctx *ctx, int x)
{
	t_ray_params	p;
	t_wall_ctx		w;
	int				o;
	double			d;

	p.pos_x = cub->pos_x;
	p.pos_y = cub->pos_y;
	p.ray_dir_x = cub->dir_x + cub->plane_x
		* (2 * x / (double)ctx->width - 1);
	p.ray_dir_y = cub->dir_y + cub->plane_y
		* (2 * x / (double)ctx->width - 1);
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