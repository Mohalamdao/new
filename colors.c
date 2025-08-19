#include "cub3d.h"

// Fonction 1 : Convertir une string RGB en nombre
int parse_rgb_string(char *rgb_str)
{
    char **rgb_parts;
    int r, g, b, color;
    
    if (!rgb_str)
        return (0x000000); // Noir par défaut
    
    rgb_parts = ft_split(rgb_str, ',');
    if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2])
        return (0x000000);
    
    r = ft_atoi(rgb_parts[0]);
    g = ft_atoi(rgb_parts[1]);
    b = ft_atoi(rgb_parts[2]);
    
    // Convertir en format 0xRRGGBB
    color = (r << 16) | (g << 8) | b;
    
    // Libérer la mémoire (tu peux faire ça plus proprement si tu veux)
    free(rgb_parts[0]);
    free(rgb_parts[1]);
    free(rgb_parts[2]);
    free(rgb_parts);
    
    return (color);
}

// Fonction 2 : Initialiser les couleurs depuis les données parsées
void init_colors(struct cub3d *cub, int *floor_color, int *ceiling_color)
{
    printf("🎨 Parsing des couleurs...\n");
    
    *floor_color = parse_rgb_string(cub->floor);
    *ceiling_color = parse_rgb_string(cub->ceiling);
    
    printf("   Sol : %s → 0x%06X\n", cub->floor, *floor_color);
    printf("   Plafond : %s → 0x%06X\n", cub->ceiling, *ceiling_color);
}
