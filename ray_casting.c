#include "cub3d.h"

// Fonction pour déterminer l'orientation du mur touché
int get_wall_orientation_dda(int side, int step_x, int step_y)
{
    if (side == 0) {  // Intersection verticale (NS wall)
        return (step_x > 0) ? 0 : 2;
    } else {  // Intersection horizontale (EW wall)
        return (step_y > 0) ? 3 : 1;
    }
}

// Algorithme DDA pour le raycasting - VERSION CORRIGÉE
double cast_single_ray_with_orientation(t_cub3d *cub, double pos_x, double pos_y, 
                                       double ray_dir_x, double ray_dir_y, int *orientation)
{
    // Position actuelle dans la grille
    int map_x = (int)pos_x;
    int map_y = (int)pos_y;
    
    // Distance entre les intersections consécutives
    double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
    double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
    
    // Direction du pas et distance jusqu'à la première intersection
    int step_x, step_y;
    double side_dist_x, side_dist_y;
    
    // Calcul pour l'axe X
    if (ray_dir_x < 0) {
        step_x = -1;
        side_dist_x = (pos_x - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
    }
    
    // Calcul pour l'axe Y
    if (ray_dir_y < 0) {
        step_y = -1;
        side_dist_y = (pos_y - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
    }
    
    // Algorithme DDA
    int hit = 0;
    int side;
    
    while (hit == 0) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        
        if (map_y < 0 || map_y >= cub->height || map_x < 0 || map_x >= cub->width) {
            break;
        }
        
        if (cub->map[map_y] && map_x < (int)strlen(cub->map[map_y]) && 
            cub->map[map_y][map_x] == '1') {
            hit = 1;
        }
    }
    
    // 🔧 CORRECTION CRITIQUE : Calculer la distance perpendiculaire avec plus de précision
    double perp_wall_dist;
    if (side == 0) {
        perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
    } else {
        perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;
    }
    
    // 🔧 CORRECTION 1 : Calcul de wall_x avec DOUBLE PRÉCISION
    double wall_hit_x, wall_hit_y;
    
    // Calculer la position exacte de l'intersection
    wall_hit_x = pos_x + perp_wall_dist * ray_dir_x;
    wall_hit_y = pos_y + perp_wall_dist * ray_dir_y;
    
    // 🔧 CORRECTION 2 : Calculer wall_x selon l'orientation, pas le side
    if (side == 0) {
        // Mur vertical (intersection NS) : utiliser Y
        cub->wall_x = wall_hit_y;
    } else {
        // Mur horizontal (intersection EW) : utiliser X  
        cub->wall_x = wall_hit_x;
    }
    
    // 🔧 CORRECTION 3 : Garder la partie fractionnaire avec plus de précision
    cub->wall_x = cub->wall_x - floor(cub->wall_x);
    
    // S'assurer que wall_x est dans [0, 1)
    if (cub->wall_x < 0) cub->wall_x = 0;
    if (cub->wall_x >= 1.0) cub->wall_x = 0.999999;
    
    // Déterminer l'orientation du mur
    *orientation = get_wall_orientation_dda(side, step_x, step_y);
    
    // 🔧 CORRECTION 4 : Protection plus stricte contre les distances trop petites
    if (perp_wall_dist < 0.01) perp_wall_dist = 0.01;
    
    return perp_wall_dist;
}

void render_3d_view(t_cub3d *cub, char *img_data, int line_length, 
                   int width, int height)
{
    int floor_color, ceiling_color;
    
    printf("🔮 Ray-casting 3D DDA : %d rayons\n", width);
    
    // Initialiser les couleurs depuis le fichier
    init_colors(cub, &floor_color, &ceiling_color);
    
    // Utiliser les valeurs déjà initialisées dans ta structure
    int x = 0;
    while (x < width) {
        double camera_x = 2 * x / (double)width - 1;
        double ray_dir_x = cub->dir_X + cub->plane_X * camera_x;
        double ray_dir_y = cub->dir_Y + cub->plane_Y * camera_x;
        
        int wall_orientation;
        double wall_dist = cast_single_ray_with_orientation(cub, cub->pos_X, cub->pos_Y, 
                                                           ray_dir_x, ray_dir_y, &wall_orientation);
                                                           // DEBUG temporaire
        draw_wall_column_textured(cub, img_data, line_length, x, height, wall_dist, 
                                 floor_color, ceiling_color, wall_orientation);
        x++;
    }
}
