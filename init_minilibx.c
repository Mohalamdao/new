/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:44:57 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:44:58 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, void *param)
{
	t_cub3d	*cub;
	int		changed;

	cub = (t_cub3d *)param;
	if (keycode == 65307)
		exit(0);
	changed = 0;
	if (is_forward(keycode) && ++changed)
		move_player_forward_back(cub, 1);
	else if (is_backward(keycode) && ++changed)
		move_player_forward_back(cub, 0);
	else if (is_strafe_left(keycode) && ++changed)
		move_player_strafe(cub, 0);
	else if (is_strafe_right(keycode) && ++changed)
		move_player_strafe(cub, 1);
	else if (is_rot_left(keycode) && ++changed)
		rotate_camera(cub, 0);
	else if (is_rot_right(keycode) && ++changed)
		rotate_camera(cub, 1);
	if (changed)
		refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	put_pixel_to_image(t_imgctx *img, int x, int y, int color)
{
	char	*px;

	px = img->data + (y * img->ll + x * 4);
	*(int *)px = color;
}

void	init_textures_safe(t_cub3d *cub)
{
	cub->no_wall = NULL;
	cub->so_wall = NULL;
	cub->ea_wall = NULL;
	cub->we_wall = NULL;
	load_wall_textures(cub);
	load_remaining_textures(cub);
}

void	draw_map_to_image_ctx(t_cub3d *cub, t_imgbuf *im, int w, int h)
{
	t_render_ctx	ctx;

	ctx.img_data = im->data;
	ctx.line_length = im->ll;
	ctx.width = w;
	ctx.height = h;
	init_colors(cub, &ctx.floor_color, &ctx.ceiling_color);
	render_3d_view(cub, &ctx);
}
