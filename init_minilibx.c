/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:30:00 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 19:56:16 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_imgbuf
{
	void	*img;
	char	*data;
	int		bpp;
	int		ll;
	int		endian;
}	t_imgbuf;

static int	is_forward(int k)
{
	return (k == 119 || k == 87);
}

static int	is_backward(int k)
{
	return (k == 115 || k == 83);
}

static int	is_strafe_left(int k)
{
	return (k == 97 || k == 65);
}

static int	is_strafe_right(int k)
{
	return (k == 100 || k == 68);
}

static int	is_rot_left(int k)
{
	return (k == 65361);
}

static int	is_rot_right(int k)
{
	return (k == 65363);
}

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

static void	draw_map_to_image_ctx(t_cub3d *cub, t_imgbuf *im, int w, int h)
{
	t_render_ctx	ctx;

	ctx.img_data = im->data;
	ctx.line_length = im->ll;
	ctx.width = w;
	ctx.height = h;
	init_colors(cub, &ctx.floor_color, &ctx.ceiling_color);
	render_3d_view(cub, &ctx);
}

void	check_and_fix_dimensions(t_cub3d *cub)
{
	if (cub->width <= 0 || cub->width > 100
		|| cub->height <= 0 || cub->height > 100)
	{
		cub->width = 10;
		cub->height = 8;
	}
}

void	setup_mlx_and_window(t_cub3d *cub)
{
	int	ww;
	int	wh;

	ww = cub->width * TILE_SIZE;
	wh = cub->height * TILE_SIZE;
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		exit(1);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, ww, wh, "Cub3D");
	if (!cub->win_ptr)
		exit(1);
}

void	refresh_display(t_cub3d *cub, void *mlx, void *win)
{
	t_imgbuf	im;
	int			ww;
	int			wh;

	ww = cub->width * TILE_SIZE;
	wh = cub->height * TILE_SIZE;
	im.img = mlx_new_image(mlx, ww, wh);
	if (!im.img)
		exit(1);
	im.data = mlx_get_data_addr(im.img, &im.bpp, &im.ll, &im.endian);
	draw_map_to_image_ctx(cub, &im, ww, wh);
	mlx_put_image_to_window(mlx, win, im.img, 0, 0);
	mlx_destroy_image(mlx, im.img);
}

void	init_minilibx(t_cub3d *cub)
{
	t_imgbuf	im;
	int			ww;
	int			wh;

	check_and_fix_dimensions(cub);
	setup_mlx_and_window(cub);
	init_textures_safe(cub);
	ww = cub->width * TILE_SIZE;
	wh = cub->height * TILE_SIZE;
	im.img = mlx_new_image(cub->mlx_ptr, ww, wh);
	if (!im.img)
		exit(1);
	im.data = mlx_get_data_addr(im.img, &im.bpp, &im.ll, &im.endian);
	draw_map_to_image_ctx(cub, &im, ww, wh);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, im.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, im.img);
	mlx_hook(cub->win_ptr, 2, 1L << 0, handle_keypress, cub);
	mlx_hook(cub->win_ptr, 17, 0, close_window, NULL);
	mlx_loop(cub->mlx_ptr);
}
