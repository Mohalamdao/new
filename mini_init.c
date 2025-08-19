/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:37:37 by molamdao          #+#    #+#             */
/*   Updated: 2025/06/22 08:43:14 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int handle_keypress(int keycode, void *param)
// {
//     (void)param;
//     if (keycode == 65307)
//         exit (0);
//     return(0);
// }

// int close_window(void   *param)
// {
//     (void)param;
//     exit(0);
//     return (0);
// }
void init_mini(struct cub3d *cub) 
{
    void *mlx;
    void *win;
    int map_width = 10; // Largeur de la carte en cases
    int map_height = 8; // Hauteur de la carte en cases
    int window_width = map_width * TILE_SIZE; // Largeur de la fenêtre
    int window_height = map_height * TILE_SIZE; // Hauteur de la fenêtre

    cub->EA_text = "rien";
    mlx = mlx_init();


    // Création de la fenêtre avec la taille de la carte
    win = mlx_new_window(mlx, window_width, window_height, "cub3D");

    // Afficher la carte case par case
    int x, y;
    char *map[] = {
        "1111111111",
        "1000000001",
        "1011111101",
        "1000000001",
        "1111111111",
    };
    
    printf("map W = %d\n", map_width);
    printf("map H = %d\n", map_height);
    for (y = 0; y < map_height; y++) {
        for (x = 0; x < map_width; x++) {
            if (map[y][x] == '1') { // Si c'est un mur
                // Remplir la case avec une couleur (par exemple, rouge pour les murs)
                mlx_pixel_put(mlx, win, x * TILE_SIZE, y * TILE_SIZE, 0xFF0000);
            } else if (map[y][x] == '0') { // Si c'est un espace vide
                // Remplir la case avec une autre couleur (par exemple, bleu pour les espaces)
                mlx_pixel_put(mlx, win, x * TILE_SIZE, y * TILE_SIZE, 0x0000FF);
            }
        }
    }

    // mlx_key_hook(win, handle_keypress, NULL);
    // mlx_hook(win, 17, 0, close_window, NULL);
    // mlx_hook(win, 2, 1L<<0, handle_keypress, NULL);

    mlx_loop(mlx); // Démarrer la boucle MLX

}


    // cub->WE_WALL = mlx_xpm_file_to_image(mlx, cub->WE_text, &width,
    //     &height);
    // cub->EA_WALL = mlx_xpm_file_to_image(mlx, cub->EA_text, &width,
    //     &height);
    // cub->SO_WALL = mlx_xpm_file_to_image(mlx, cub->SO_text, &width,
    //     &height);
    // cub->NO_WALL = mlx_xpm_file_to_image(mlx, cub->NO_text, &width,
    //     &height);
