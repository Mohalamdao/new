/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:18:55 by molamdao          #+#    #+#             */
/*   Updated: 2025/07/24 23:06:34 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int check_path_text(char *str)
{
    if (access(str, F_OK) == -1)
    {
        printf("Erreur : inaccessible texture\n");
        return(1);
    }
    return(0);
}
int check_rgb(char *str, int i, int j)
{
    char **rgb;

    rgb = ft_split(str,',');
    while(rgb[i])
        i++;
    if(i != 3)
        return(1);
    i = 0;
    while (rgb[i])
    {
        j = 0;
        while(rgb[i][j] == ' ')
                j++;
        while(rgb[i][j])
        {
            if(rgb[i][j] > '9' || rgb[i][j] < '0')
                return(1);
            j++;
        }
        if(ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
            return(1);
        i++;
    }
    return(0);
}
int check_rgb_text(struct cub3d cub)
{
    if(check_path_text(cub.EA_text) == 1)
        return(1);
    if(check_path_text(cub.NO_text) == 1)
        return(1);
    if(check_path_text(cub.EA_text) == 1)
        return(1);
    if(check_path_text(cub.SO_text) == 1)
        return(1);
    if(check_rgb(cub.ceiling,0,0) == 1)
        return(1);
    if(check_rgb(cub.floor,0,0) == 1)
        return(1);
    return(0);
}
void init_player_direction(struct cub3d *cub)
{
    cub->pos_X = cub->pos_j_player + 0.5;
    cub->pos_Y = cub->pos_i_player + 0.5;
    
    printf("🧭 Initialisation joueur: position (%.2f, %.2f), orientation '%c'\n", 
           cub->pos_X, cub->pos_Y, cub->orientation);
    
    if(cub->orientation == 'N')
    {
        cub->dir_X = 0;
        cub->dir_Y = -1;
        cub->plane_X = 0.66;
        cub->plane_Y = 0;
    }
    else if(cub->orientation == 'S')
    {
        cub->dir_X = 0;
        cub->dir_Y = 1;
        cub->plane_X = -0.66;  // CORRECTION : était inversé
        cub->plane_Y = 0;
    }
    else if(cub->orientation == 'E')
    {
        cub->dir_X = 1;
        cub->dir_Y = 0;
        cub->plane_X = 0;
        cub->plane_Y = 0.66;
    }
    else if(cub->orientation == 'W')
    {
        cub->dir_X = -1;
        cub->dir_Y = 0;
        cub->plane_X = 0;        // CORRECTION : était -0.66
        cub->plane_Y = -0.66;    // CORRECTION : était 0
    }
    
    printf("✅ Direction: (%.2f, %.2f), Plan: (%.2f, %.2f)\n", 
           cub->dir_X, cub->dir_Y, cub->plane_X, cub->plane_Y);
}
