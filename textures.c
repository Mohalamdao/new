#include "cub3d.h"

// ✅ Fonction 1 : Charger les textures avec gestion d'erreurs
void load_wall_textures(struct cub3d *cub)
{
    int width, height;
    
    printf("🖼️  Chargement des textures...\n");
    
    if (!cub || !cub->mlx_ptr) {
        printf("⚠️  MLX non initialisé\n");
        return;
    }
    
    // Charger texture Nord
    if (cub->NO_text) {
        cub->NO_WALL = mlx_xpm_file_to_image(cub->mlx_ptr, cub->NO_text, &width, &height);
        if (cub->NO_WALL)
            printf("✅ Texture Nord: %s\n", cub->NO_text);
        else
            printf("⚠️  Échec Nord: %s\n", cub->NO_text);
    }
    
    // Charger texture Sud  
    if (cub->SO_text) {
        cub->SO_WALL = mlx_xpm_file_to_image(cub->mlx_ptr, cub->SO_text, &width, &height);
        if (cub->SO_WALL)
            printf("✅ Texture Sud: %s\n", cub->SO_text);
        else
            printf("⚠️  Échec Sud: %s\n", cub->SO_text);
    }
}

// Fonction 2 : Charger textures Est et Ouest
void load_remaining_textures(struct cub3d *cub)
{
    int width, height;
    
    // Charger texture Est
    if (cub->EA_text) {
        cub->EA_WALL = mlx_xpm_file_to_image(cub->mlx_ptr, cub->EA_text, &width, &height);
        if (cub->EA_WALL)
            printf("✅ Texture Est: %s\n", cub->EA_text);
        else
            printf("⚠️  Échec Est: %s\n", cub->EA_text);
    }
    
    // Charger texture Ouest
    if (cub->WE_text) {
        cub->WE_WALL = mlx_xpm_file_to_image(cub->mlx_ptr, cub->WE_text, &width, &height);
        if (cub->WE_WALL)
            printf("✅ Texture Ouest: %s\n", cub->WE_text);
        else
            printf("⚠️  Échec Ouest: %s\n", cub->WE_text);
    }
    
    printf("🎨 Chargement terminé\n");
}

// Fonction 3 : Déterminer l'orientation d'un mur
int get_wall_orientation(double ray_dir_x, double ray_dir_y, double hit_x, double hit_y)
{
    (void)hit_x;
    (void)hit_y;
    
    if (ray_dir_x > 0 && ray_dir_x > fabs(ray_dir_y))
        return (1); // Est
    else if (ray_dir_x < 0 && (-ray_dir_x) > fabs(ray_dir_y))
        return (3); // Ouest
    else if (ray_dir_y > 0)
        return (2); // Sud
    else
        return (0); // Nord
}

// Fonction 4 : Sélectionner la texture selon l'orientation
void* get_texture_image(struct cub3d *cub, int orientation)
{
    if (!cub)
        return (NULL);  
    if (orientation == 0 && cub->NO_WALL)
        return (cub->NO_WALL);
    else if (orientation == 1 && cub->EA_WALL)
        return (cub->EA_WALL);
    else if (orientation == 2 && cub->SO_WALL)
        return (cub->SO_WALL);
    else if (orientation == 3 && cub->WE_WALL)
        return (cub->WE_WALL);
    else
        return (NULL);
}
