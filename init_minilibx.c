#include "cub3d.h"

int handle_keypress(int keycode, void *param)
{
    struct cub3d *cub = (struct cub3d *)param;
    
    if (keycode == 65307)
        exit(0);
    else if (keycode == 119 || keycode == 87) 
    { // W
        move_player_forward_back(cub, 1);
        refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
    }
    else if (keycode == 115 || keycode == 83) 
    { // S
        move_player_forward_back(cub, 0);
        refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
    }
    else if (keycode == 97 || keycode == 65) 
    {// A (gauche)
        move_player_strafe(cub, 0);
        refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
    }
    else if (keycode == 100 || keycode == 68) 
    {// D (droite)
        move_player_strafe(cub, 1);
        refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
    }
    else if (keycode == 65361) 
    {// Fleche gauche
        rotate_camera(cub, 0);
        refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
    }
    else if (keycode == 65363) 
    {// Fleche droite  
        rotate_camera(cub, 1);
        refresh_display(cub, cub->mlx_ptr, cub->win_ptr);
    }
    return (0);
}

int close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

void put_pixel_to_image(char *img_data, int x, int y, int color, int line_length)
{
    char *pixel = img_data + (y * line_length + x * 4);
    *(int *)pixel = color;
}

void init_textures_safe(struct cub3d *cub)
{
    printf("🎨 Tentative de chargement des textures...\n");
    cub->NO_WALL = NULL;
    cub->SO_WALL = NULL;
    cub->EA_WALL = NULL;
    cub->WE_WALL = NULL;
    load_wall_textures(cub);
    load_remaining_textures(cub);
    
    printf("✅ Initialisation textures terminée (couleurs utilisées si échec)\n");
}

void draw_map_to_image(struct cub3d *cub, char *img_data, int line_length, 
                      int width, int height)
{
    render_3d_view(cub, img_data, line_length, width, height);
}

void check_and_fix_dimensions(struct cub3d *cub)
{
    printf("🔍 DIAGNOSTIC: cub->width = %d, cub->height = %d\n", cub->width, cub->height);
    
    if (cub->width <= 0 || cub->width > 100 || cub->height <= 0 || cub->height > 100) {
        printf("⚠️  VALEURS ABERRANTES DÉTECTÉES ! Correction temporaire...\n");
        printf("   Ancienne taille : %dx%d\n", cub->width, cub->height);
        
        cub->width = 10;
        cub->height = 8;
        
        printf("   Nouvelle taille : %dx%d\n", cub->width, cub->height);
        printf("   → Fenêtre sera : %dx%d pixels\n", 
               cub->width * TILE_SIZE, cub->height * TILE_SIZE);
    }
}

void setup_mlx_and_window(struct cub3d *cub)
{
    int window_width = cub->width * TILE_SIZE;
    int window_height = cub->height * TILE_SIZE;
    
    printf("🔧 Initialisation MLX...\n");
    cub->mlx_ptr = mlx_init();
    if (!cub->mlx_ptr) {
        printf("❌ Erreur MLX init\n");
        exit(1);
    }
    
    printf("🖼️  Création fenêtre %dx%d...\n", window_width, window_height);
    cub->win_ptr = mlx_new_window(cub->mlx_ptr, window_width, window_height, "Cub3D");
    if (!cub->win_ptr) {
        printf("❌ Erreur création fenêtre\n");
        exit(1);
    }
    
    printf("✅ Fenêtre créée : %dx%d\n", window_width, window_height);
}

void init_minilibx(struct cub3d *cub)
{
    void *img;
    char *img_data;
    int bits_per_pixel, line_length, endian;
    
    printf("🚀 Démarrage Cub3D sécurisé...\n");
    check_and_fix_dimensions(cub);
    setup_mlx_and_window(cub);
    init_textures_safe(cub);
    int window_width = cub->width * TILE_SIZE;
    int window_height = cub->height * TILE_SIZE;
    
    printf("🎨 Création de l'image...\n");
    img = mlx_new_image(cub->mlx_ptr, window_width, window_height);
    if (!img) {
        printf("❌ Erreur création image\n");
        exit(1);
    }
    img_data = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
    printf("🎮 Rendu de la vue 3D...\n");
    render_3d_view(cub, img_data, line_length, window_width, window_height);
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, img, 0, 0);
    printf("✅ Cub3D lancé ! Utilisez WASD + flèches pour bouger\n");
    mlx_hook(cub->win_ptr, 2, 1L<<0, handle_keypress, cub);
    //mlx_hook(cub->win_ptr, 3, 1L<<1, key_release, cub);
    mlx_hook(cub->win_ptr, 17, 0, close_window, NULL);
    mlx_loop(cub->mlx_ptr);
}
