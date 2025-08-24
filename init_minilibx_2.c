/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minilibx_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:44:41 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:44:42 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
