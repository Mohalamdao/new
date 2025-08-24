#include "cub3d.h"

int	handle_keypress(int keycode, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (keycode == 65307)
		exit(0);
	else if (keycode == 119 || keycode == 87)
	{
		move_player_forward_back(cub, 1);
		refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
	}
	else if (keycode == 115 || keycode == 83)
	{
		move_player_forward_back(cub, 0);
		refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
	}
	else if (keycode == 97 || keycode == 65)
	{
		move_player_strafe(cub, 0);
		refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
	}
	else if (keycode == 100 || keycode == 68)
	{
		move_player_strafe(cub, 1);
		refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
	}
	else if (keycode == 65361)
	{
		rotate_camera(cub, 0);
		refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
	}
	else if (keycode == 65363)
	{
		rotate_camera(cub, 1);
		refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
	}
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	put_pixel_to_image(char *img_data, int x, int y, int color,
			int line_length)
{
	char	*pixel;

	pixel = img_data + (y * line_length + x * 4);
	*(int *)pixel = color;
}

void	init_textures_safe(t_cub3d *cub)
{
	cub->NO_WALL = NULL;
	cub->SO_WALL = NULL;
	cub->EA_WALL = NULL;
	cub->WE_WALL = NULL;
	load_wall_textures(cub);
	load_remaining_textures(cub);
}

void	draw_map_to_image(t_cub3d *cub, char *img_data, int line_length,
			int width, int height)
{
	render_3d_view(cub, img_data, line_length, width, height);
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
	int	window_width;
	int	window_height;

	window_width = cub->width * TILE_SIZE;
	window_height = cub->height * TILE_SIZE;
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		exit(1);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, window_width, window_height,
		"Cub3D");
	if (!cub->win_ptr)
		exit(1);
}

void	init_minilibx(t_cub3d *cub)
{
	void	*img;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		window_width;
	int		window_height;

	check_and_fix_dimensions(cub);
	setup_mlx_and_window(cub);
	init_textures_safe(cub);
	window_width = cub->width * TILE_SIZE;
	window_height = cub->height * TILE_SIZE;
	img = mlx_new_image(cub->mlx_ptr, window_width, window_height);
	if (!img)
		exit(1);
	img_data = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	render_3d_view(cub, img_data, line_length, window_width, window_height);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, img, 0, 0);
	mlx_hook(cub->win_ptr, 2, 1L << 0, handle_keypress, cub);
	mlx_hook(cub->win_ptr, 17, 0, close_window, NULL);
	mlx_loop(cub->mlx_ptr);
}
