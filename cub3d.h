/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:57:06 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:06:29 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 50 // Taille d'une case de la carte en pixels

# define NORTH 0
# define SOUTH 1  
# define EAST  2
# define WEST  3

# define KEY_W       13
# define KEY_A       0
# define KEY_S       1
# define KEY_D       2
# define KEY_LEFT    123
# define KEY_RIGHT   124
# define KEY_ESC     53

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "gnl/get_next_line.h"

typedef struct s_imgbuf
{
	void	*img;
	char	*data;
	int		bpp;
	int		ll;
	int		endian;
}	t_imgbuf;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

typedef struct s_cub3d
{
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	char	*floor;
	char	*ceiling;
	char	**map;
	int		pos_i_player;
	int		pos_j_player;
	void	*we_wall;
	void	*so_wall;
	void	*no_wall;
	void	*ea_wall;
	char	orientation;
	double	wall_x;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		width;
	int		height;
	int		count;
	void	*mlx_ptr;
	void	*win_ptr;
	t_keys	keys;
}	t_cub3d;

typedef struct s_imginfo
{
	void	*img;
	char	*data;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
}	t_imginfo;

typedef struct s_ray_params
{
	double	pos_x;
	double	pos_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		*orientation;
}	t_ray_params;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
}	t_ray;

typedef struct s_render_ctx
{
	char	*img_data;
	int		line_length;
	int		width;
	int		height;
	int		floor_color;
	int		ceiling_color;
}	t_render_ctx;

typedef struct s_imgctx
{
	char	*data;
	int		ll;
}	t_imgctx;

typedef struct s_wall_ctx
{
	t_imgctx	img;
	int			x;
	int			width;
	int			height;
	double		wall_dist;
	int			orientation;
	int			floor_color;
	int			ceiling_color;
}	t_wall_ctx;

typedef struct s_tex
{
	int		bpp;
	int		ll;
	int		endian;
	char	*data;
}	t_tex;

typedef struct s_wvars
{
	int		line_h;
	int		y0;
	int		y1;
	int		tex_w;
	int		tex_h;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}	t_wvars;

typedef struct s_render_ctx	t_render_ctx;
typedef struct s_wall_ctx	t_wall_ctx;
typedef struct s_ray_params	t_ray_params;

// PROTOTYPE

// COLORS.C

int		parse_rgb_string(char *rgb_str);
void	init_colors(t_cub3d *cub, int *floor_color, int *ceiling_color);

// CONTROLS.C

static void	update_position(t_cub3d *cub, double new_x, double new_y);
void		move_player_forward_back(t_cub3d *cub, int forward);
void		move_player_strafe(t_cub3d *cub, int right);
static void	rotate_left(t_cub3d *cub, double rot_speed, double old_dir_x, double old_plane_x);
static void	rotate_right(t_cub3d *cub, double rot_speed, double old_dir_x, double old_plane_x);
void		rotate_camera(t_cub3d *cub, int left);

// FILE_CONTENT.C

void		strip_newline(char *line);
char		**content_file(char *file, int count);
int			count_map_lines(char **file_content, int start_index);
static void	set_texture_color(t_cub3d *cub, char *line);
void		initialization_struct(t_cub3d *cub, char **file_content, int i, int j);

// FT_SPLIT.C

static int	check_separator(char c, char charset);
static int	count_strings(char *str, char charset);
static char	*ft_mallocword(char *str, char charset);
static void	ft_free(char **strr);
char		**ft_split(char const *str, char charset);

// INIT_MINILIBX.C

static int		is_forward(int k);
static int		is_backward(int k);
static int		is_strafe_left(int k);
static int		is_strafe_right(int k);
static int		is_rot_left(int k);
static int		is_rot_right(int k);
int				handle_keypress(int keycode, void *param);
int				close_window(void *param);
void			put_pixel_to_image(t_imgctx *img, int x, int y, int color);
void			init_textures_safe(t_cub3d *cub);
static void		draw_map_to_image_ctx(t_cub3d *cub, t_imgbuf *im, int w, int h);
void			check_and_fix_dimensions(t_cub3d *cub);
void			setup_mlx_and_window(t_cub3d *cub);
void			refresh_display(t_cub3d *cub, void *mlx, void *win);
void			init_minilibx(t_cub3d *cub);

// PARSING.C

int	check_around(t_cub3d *cub, int i, int j);
int	check_outline(t_cub3d *cub);
int	check_element_map(t_cub3d *cub, int i, int j);
int	pos_player(t_cub3d *cub, int i, int j);
int	parsing(t_cub3d *cub);

// PARSING_2.C

int			check_path_text(char *str);
static int	validate_rgb_part(char *p);
static int	count_parts(char **rgb);
int			check_rgb(char *str, int i, int j);
int			check_rgb_text(t_cub3d cub);
static void	set_dir_plane_ns(t_cub3d *cub, int south);
static void	set_dir_plane_ew(t_cub3d *cub, int west);
void		init_player_direction(t_cub3d *cub);


// RAY_CASTING.C

static int		get_wall_orientation_dda(int side, int step_x, int step_y);
static void		init_dda_pos_delta(t_ray *r, t_ray_params *p);
static void		init_dda_steps(t_ray *r, t_ray_params *p);
static void		perform_dda(t_cub3d *cub, t_ray *r);
static double	calc_perp_dist(t_cub3d *cub, t_ray *r, t_ray_params *p);
double			cast_single_ray_with_orientation(t_cub3d *cub, t_ray_params *p);
static void		render_column(t_cub3d *cub, t_render_ctx *ctx, int x);
void			render_3d_view(t_cub3d *cub, t_render_ctx *ctx);


// TEXTURE_UTILS.C

char	*get_texture_data(void *texture_img, int *line_length);
void	secure_texture_coords(int *tex_x, int *tex_y);
int		read_texture_pixel(char *texture_data, int tex_x, int tex_y, int line_length);
int		get_texture_pixel(t_cub3d *cub, int orientation, int tex_x, int tex_y);
int		get_texture_color(t_cub3d *cub, int orientation);


// TEXTURE.C

void	load_wall_textures(t_cub3d *cub);
void	load_remaining_textures(t_cub3d *cub);
int		get_wall_orientation(double ray_dir_x, double ray_dir_y, double hit_x, double hit_y);
void	*get_texture_image(t_cub3d *cub, int orientation);


// UTILS.C

char	*ft_strdup(char *src);
char	*skip_space(char *str);
int		ft_atoi(const char *str);

// WALL_RENDERING.C

static int	read_pixel_from_texture(void *img, int tx, int ty);
static void	draw_flat_top(t_wall_ctx *c, int y0);
static void	draw_flat_bottom(t_wall_ctx *c, int y1);
static void	setup_strip_bounds(t_wall_ctx *c, t_wvars *v);
static void	prepare_tex_coords(t_cub3d *cub, t_wall_ctx *c, t_wvars *v);
static void	draw_wall_pixel_ctx(t_cub3d *cub, t_wall_ctx *c, t_wvars *v);
void		draw_wall_column_textured(t_cub3d *cub, t_wall_ctx *c);


#endif
