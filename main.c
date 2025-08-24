/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molamdao <molamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:47:49 by molamdao          #+#    #+#             */
/*   Updated: 2025/08/24 14:33:34 by molamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_cub3d	cub;
    
    char **file_content;
    file_content = NULL;
    if(ac != 2)
    {
        printf("error arg\n");
        return(1);
    }
    else
        file_content = content_file(av[1], 0);
    if (!file_content)
    {
        printf("Error: Cannot read file\n");
        return(1);
    }
    initialization_struct(&cub, file_content, 0, 0);
    if(parsing(&cub) == 1)
    {
        printf("Error: Map parsing failed\n");
        return(1);
    }
    if(check_rgb_text(cub) == 1)
    {
        printf("Warning: Some textures/colors invalid, using defaults\n");
    }
    init_player_direction(&cub);
    init_minilibx(&cub);
    return (0);
}