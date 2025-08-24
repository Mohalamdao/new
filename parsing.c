/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molamdao <molamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:48:00 by molamdao          #+#    #+#             */
/*   Updated: 2025/08/24 14:33:34 by molamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_around(t_cub3d *cub , int i, int j)
{
    if(!cub->map[i][j + 1] || !cub->map[i][j - 1 ] || !cub->map[i + 1][j] || !cub->map[i - 1][j]
        || cub->map[i][j + 1] == ' '|| cub->map[i][j - 1 ] == ' '|| cub->map[i + 1][j] == ' ' || cub->map[i - 1][j] == ' ')
        return(1);
    return(0);
}
int check_outline(t_cub3d *cub)
{
    int i;

    i = -1;
    while(cub->map[++i])
    {
        int j = 0;
        while(cub->map[i][j] == ' ' || cub->map[i][j] == '\t')
            j++;
        if(cub->map[i][j] != '1')
            return(1);
        while(cub->map[i][j])
        {
            if(cub->map[i][j] == '0')
            {
                if(check_around(cub,i,j) == 1)
                {
                    printf("Error : invalid blank space \n");
                    return(1);
                }
            }
            j++;
        }
    }
    return(0);
}
int check_element_map(t_cub3d *cub, int i, int j)
{
    if(cub->map[0] == NULL)
    {
        printf("Error : You have to put a map");
        return(1);
    }
    while(cub->map[++i])
    {
        j = -1;
        if(cub->map[i][0] == '\0')
        {
            printf("Error : empty line in the map");
            return(1);
        }
        while(cub->map[i][++j])
        {
            if(cub->map[i][j] != '1' && cub->map[i][j] != '0' && cub->map[i][j] != 'N' &&
                cub->map[i][j] != 'E' && cub->map[i][j] != 'S' && cub->map[i][j] != 'W' &&  cub->map[i][j] != ' ')
            {
                printf("Error : The map contains unauthorized elements\n");
                return(1);
            }
        }    
    }
    return(0);
}

int pos_player(t_cub3d *cub, int i, int j)  // ← Enlever "int width"
{   
    cub->count = 0;
    cub->width = 0;  // Initialiser à 0
    
    while(cub->map[++i])
    {
        j = -1;
        while(cub->map[i][++j])
        {
            if( cub->map[i][j] == 'N' || cub->map[i][j] == 'E' || 
                cub->map[i][j] == 'S' || cub->map[i][j] == 'W')
            {
                cub->count++;
                cub->pos_i_player = i;
                cub->pos_j_player = j;
                cub->orientation = cub->map[i][j];
                cub->map[i][j] = '0';
            }
        } 
        
        // CORRECTION : Garder la largeur maximale trouvée
        if(j > cub->width)
            cub->width = j;
    }
    cub->height = i;
    
    // AJOUT : Debug pour voir ce qu'on obtient
    printf("🔍 PARSING DEBUG: Carte trouvée = %dx%d\n", cub->width, cub->height);
    
    if(cub->count != 1)
        return(1);
    return(0);
}

int parsing(t_cub3d *cub)
{
    if(!cub->ceiling || !cub->EA_text || !cub->floor 
        || !cub->NO_text || !cub->SO_text || !cub->WE_text )
    {
        printf("Error : The file content is not correct\n");
        return(1);
    }
    if(check_element_map(cub, -1, -1) == 1)
        return(1);
    if(check_outline(cub) == 1)
    {
        printf("Error : The map is not valid \n");
        return(1);
    }
    if(pos_player(cub, -1, -1) == 1)
    {
        printf("Error : there must be 1 player \n");
        return(1);
    }
    return(0);
}
