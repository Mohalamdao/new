#include "cub3d.h"

int check_path_text(char *str)
{
    if (access(str, F_OK) == -1)
    {
        return (1);
    }
    return (0);
}

int check_rgb(char *str, int i, int j)
{
    char **rgb;

    rgb = ft_split(str, ',');
    while (rgb[i])
        i++;
    if (i != 3)
        return (1);
    i = 0;
    while (rgb[i])
    {
        j = 0;
        while (rgb[i][j] == ' ')
            j++;
        while (rgb[i][j])
        {
            if (rgb[i][j] > '9' || rgb[i][j] < '0')
                return (1);
            j++;
        }
        if (ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
            return (1);
        i++;
    }
    return (0);
}

int check_rgb_text(t_cub3d cub)
{
    if (check_path_text(cub.ea_text) == 1)
        return (1);
    if (check_path_text(cub.no_text) == 1)
        return (1);
    if (check_path_text(cub.ea_text) == 1)
        return (1);
    if (check_path_text(cub.so_text) == 1)
        return (1);
    if (check_rgb(cub.ceiling, 0, 0) == 1)
        return (1);
    if (check_rgb(cub.floor, 0, 0) == 1)
        return (1);
    return (0);
}

void init_player_direction(t_cub3d *cub)
{
    cub->pos_x = cub->pos_j_player + 0.5;
    cub->pos_y = cub->pos_i_player + 0.5;
    if (cub->orientation == 'N')
    {
        cub->dir_x = 0;
        cub->dir_y = -1;
        cub->plane_x = 0.66;
        cub->plane_y = 0;
    }
    else if (cub->orientation == 'S')
    {
        cub->dir_x = 0;
        cub->dir_y = 1;
        cub->plane_x = -0.66;
        cub->plane_y = 0;
    }
    else if (cub->orientation == 'E')
    {
        cub->dir_x = 1;
        cub->dir_y = 0;
        cub->plane_x = 0;
        cub->plane_y = 0.66;
    }
    else if (cub->orientation == 'W')
    {
        cub->dir_x = -1;
        cub->dir_y = 0;
        cub->plane_x = 0;
        cub->plane_y = -0.66;
    }
}
