#include "cub3d.h"

// Fonction 1 : Obtenir les données d'une texture (sécurisée)
char* get_texture_data(void *texture_img, int *line_length)
{
    int bits_per_pixel, endian;
    
    if (!texture_img || !line_length)
        return (NULL);
        
    return (mlx_get_data_addr(texture_img, &bits_per_pixel, line_length, &endian));
}

// Fonction 2 : Sécuriser les coordonnées de texture  
void secure_texture_coords(int *tex_x, int *tex_y)
{
    if (*tex_x < 0) *tex_x = 0;
    if (*tex_x >= 64) *tex_x = 63;
    if (*tex_y < 0) *tex_y = 0;
    if (*tex_y >= 64) *tex_y = 63;
}

// Fonction 3 : Lire un pixel dans les données de texture (sécurisée)
int read_texture_pixel(char *texture_data, int tex_x, int tex_y, int line_length)
{
    char *pixel;
    
    if (!texture_data || line_length <= 0)
        return (0xFF0000); // Rouge par défaut
    
    // ✅ Vérifications supplémentaires pour éviter segfault
    if (tex_x < 0 || tex_x >= 64 || tex_y < 0 || tex_y >= 64)
        return (0xFF0000);
        
    pixel = texture_data + (tex_y * line_length + tex_x * 4);
    return (*(int *)pixel);
}

// Fonction 4 : Obtenir pixel de texture - VERSION OPÉRATIONNELLE
int get_texture_pixel(t_cub3d *cub, int orientation, int tex_x, int tex_y)
{
    void *texture_img;
    char *texture_data;
    int line_length;
    
    // Vérifications de base
    if (!cub)
        return (get_texture_color(cub, orientation));
    
    texture_img = get_texture_image(cub, orientation);
    if (!texture_img)
        return (get_texture_color(cub, orientation)); // Fallback couleur
    
    texture_data = get_texture_data(texture_img, &line_length);
    if (!texture_data)
        return (get_texture_color(cub, orientation)); // Fallback couleur
        
    secure_texture_coords(&tex_x, &tex_y);
    return (read_texture_pixel(texture_data, tex_x, tex_y, line_length));
}

// Fonction 5 : Couleurs de fallback si textures manquantes
int get_texture_color(t_cub3d *cub, int orientation)
{
    (void)cub;
    
    if (orientation == 0) return (0xFF0000); // Rouge Nord
    else if (orientation == 1) return (0x00FF00); // Vert Est  
    else if (orientation == 2) return (0x0000FF); // Bleu Sud
    else return (0xFFFF00); // Jaune Ouest
}