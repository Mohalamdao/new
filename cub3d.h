/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molamdao <molamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:47:15 by molamdao          #+#    #+#             */
/*   Updated: 2025/08/24 14:33:34 by molamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define TILE_SIZE 50 // Taille d'une case de la carte en pixels

#define NORTH 0
#define SOUTH 1  
#define EAST  2
#define WEST  3

#define KEY_W       13
#define KEY_A       0
#define KEY_S       1
#define KEY_D       2
#define KEY_LEFT    123
#define KEY_RIGHT   124
#define KEY_ESC     53

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <math.h>
#include "mlx.h"

# include "gnl/get_next_line.h"

typedef struct s_keys
{
    int w;          
    int s;          
    int a;          
    int d;          
    int left;       
    int right;      
    int esc;        
} t_keys;

typedef struct s_cub3d
{
	char *NO_text;
	char *SO_text;
	char *WE_text;
    char *EA_text;
	char *floor;
    char *ceiling;
	char **map;
	int pos_i_player;
	int pos_j_player;
	void	*WE_WALL;
	void	*SO_WALL;
	void	*NO_WALL;
	void	*EA_WALL;
	char 	orientation;
	double		wall_x;
	double		pos_X;
	double		pos_Y;
	double		dir_X;
	double		dir_Y;
	double		plane_X;
	double		plane_Y;
	int			width;
	int			height;
	int			count;
	void	*mlx_ptr;
	void	*win_ptr;
	t_keys	keys;
} t_cub3d; 

char **content_file(char *file, int count);
void initialization_struct(t_cub3d *cub, char **file_content, int i, int j);
char	*ft_strdup(char *src);
char *skip_space(char *str);
int parsing(t_cub3d *cub);
char	**ft_split(char const *str, char charset);
int	ft_atoi(const char *str);
int check_rgb_text(t_cub3d cub);
void init_player_direction(t_cub3d *cub);
void    init_minilibx(t_cub3d *cub);
int handle_keypress(int keycode, void *param);
int close_window(void *param);
void put_pixel_to_image(char *img_data, int x, int y, int color, int line_length);
int pos_player(t_cub3d *cub, int i, int j);
void put_pixel_to_image(char *img_data, int x, int y, int color, int line_length);
void render_3d_view(t_cub3d *cub, char *img_data, int line_length, int width, int height);
double cast_single_ray(t_cub3d *cub, double pos_x, double pos_y, double ray_dir_x, double ray_dir_y);

void move_player_forward_back(t_cub3d *cub, int forward);
void move_player_strafe(t_cub3d *cub, int right);
void rotate_camera(t_cub3d *cub, int left);

void check_and_fix_dimensions(t_cub3d *cub);
void setup_mlx_and_window(t_cub3d *cub);
void refresh_display(t_cub3d *cub, void *mlx, void *win);

int parse_rgb_string(char *rgb_str);
void init_colors(t_cub3d *cub, int *floor_color, int *ceiling_color);

void load_wall_textures(t_cub3d *cub);
int get_wall_orientation(double ray_dir_x, double ray_dir_y, double hit_x, double hit_y);
int get_texture_color(t_cub3d *cub, int orientation);
double cast_single_ray_with_orientation(t_cub3d *cub, double pos_x, double pos_y, double ray_dir_x, double ray_dir_y, int *orientation);

char* get_texture_data(void *texture_img, int *line_length);
void secure_texture_coords(int *tex_x, int *tex_y);
int read_texture_pixel(char *texture_data, int tex_x, int tex_y, int line_length);
int get_texture_pixel(t_cub3d *cub, int orientation, int tex_x, int tex_y);
void* get_texture_image(t_cub3d *cub, int orientation);

void calculate_texture_coords(t_cub3d *cub, int y, int wall_start, int wall_height, int wall_orientation, int *tex_x, int *tex_y);
void draw_ceiling_pixel(char *img_data, int line_length, int x, int y, int ceiling_color);
void draw_floor_pixel(char *img_data, int line_length, int x, int y, int floor_color);
void draw_wall_pixel(t_cub3d *cub, char *img_data, int line_length, int x, int y, int wall_orientation, int tex_x, int tex_y);
void draw_wall_column_textured(t_cub3d *cub, char *img_data, int line_length, int x, int height, double wall_dist, int floor_color, int ceiling_color, int wall_orientation);

void load_remaining_textures(t_cub3d *cub);

int key_release(int keycode, t_cub3d *cub);
void set_hit_coordinates(double hit_x, double hit_y, int orientation);

#endif