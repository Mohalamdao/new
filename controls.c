#include "cub3d.h"

// Fonction 1 : Déplacer le joueur vers l'avant/arrière
void move_player_forward_back(struct cub3d *cub, int forward)
{
    double move_speed = 0.1;
    double new_x, new_y;
    
    if (forward) {
        new_x = cub->pos_X + cub->dir_X * move_speed;
        new_y = cub->pos_Y + cub->dir_Y * move_speed;
    } else {
        new_x = cub->pos_X - cub->dir_X * move_speed;
        new_y = cub->pos_Y - cub->dir_Y * move_speed;
    }
    
    // Vérifier collision avec les murs
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    if (map_y >= 0 && map_y < cub->height && map_x >= 0 && map_x < cub->width) {
        if (cub->map[map_y] && cub->map[map_y][map_x] != '1') {
            cub->pos_X = new_x;
            cub->pos_Y = new_y;
        }
    }
}

// Fonction 2 : Déplacer le joueur gauche/droite (strafe)
void move_player_strafe(struct cub3d *cub, int right)
{
    double move_speed = 0.1;
    double new_x, new_y;
    
    if (right) {
        new_x = cub->pos_X + cub->plane_X * move_speed;
        new_y = cub->pos_Y + cub->plane_Y * move_speed;
    } else {
        new_x = cub->pos_X - cub->plane_X * move_speed;
        new_y = cub->pos_Y - cub->plane_Y * move_speed;
    }
    
    // Vérifier collision
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    if (map_y >= 0 && map_y < cub->height && map_x >= 0 && map_x < cub->width) {
        if (cub->map[map_y] && cub->map[map_y][map_x] != '1') {
            cub->pos_X = new_x;
            cub->pos_Y = new_y;
        }
    }
}

// Fonction 3 : Rotation de la caméra
void rotate_camera(struct cub3d *cub, int left)
{
    double rot_speed = 0.05;
    double old_dir_x = cub->dir_X;
    double old_plane_x = cub->plane_X;
    
    if (left) {
        cub->dir_X = cub->dir_X * cos(rot_speed) - cub->dir_Y * sin(rot_speed);
        cub->dir_Y = old_dir_x * sin(rot_speed) + cub->dir_Y * cos(rot_speed);
        cub->plane_X = cub->plane_X * cos(rot_speed) - cub->plane_Y * sin(rot_speed);
        cub->plane_Y = old_plane_x * sin(rot_speed) + cub->plane_Y * cos(rot_speed);
    } else {
        cub->dir_X = cub->dir_X * cos(-rot_speed) - cub->dir_Y * sin(-rot_speed);
        cub->dir_Y = old_dir_x * sin(-rot_speed) + cub->dir_Y * cos(-rot_speed);
        cub->plane_X = cub->plane_X * cos(-rot_speed) - cub->plane_Y * sin(-rot_speed);
        cub->plane_Y = old_plane_x * sin(-rot_speed) + cub->plane_Y * cos(-rot_speed);
    }
}
// Fonction 4 : Redessiner la vue après un mouvement
void refresh_display(struct cub3d *cub, void *mlx, void *win)
{
    void *img;
    char *img_data;
    int bits_per_pixel, line_length, endian;
    int window_width = cub->width * TILE_SIZE;
    int window_height = cub->height * TILE_SIZE;
    
    // Créer une nouvelle image
    img = mlx_new_image(mlx, window_width, window_height);
    img_data = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
    
    // Redessiner la vue 3D avec la nouvelle position
    render_3d_view(cub, img_data, line_length, window_width, window_height);
    
    // Afficher la nouvelle image
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    
    // Nettoyer l'ancienne image
    mlx_destroy_image(mlx, img);
}
