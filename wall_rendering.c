#include "cub3d.h"
#include <math.h>

/* On utilise la fonction utilitaire définie ailleurs */
void put_pixel_to_image(char *img_data, int x, int y, int color, int line_length);

/* Textures utilitaires (déjà présentes dans ton projet) */
void* get_texture_image(struct cub3d *cub, int orientation);
int   get_texture_color(struct cub3d *cub, int orientation);

/* -------------------------------------------------------------------------- */
/*                        Lecture d’un pixel dans une texture                  */
/* -------------------------------------------------------------------------- */

static int read_pixel_from_texture(void *img, int tx, int ty)
{
    if (!img) return 0;
    int bpp, line_len, endian;
    char *data = mlx_get_data_addr(img, &bpp, &line_len, &endian);
    if (!data || bpp <= 0) return 0;
    char *px = data + ty * line_len + tx * (bpp / 8);
    return *(int *)px;
}

/* -------------------------------------------------------------------------- */
/*                              Dessin d’un pixel                               */
/* -------------------------------------------------------------------------- */

// pas de static, signature identique à cub3d.h
void draw_wall_pixel(struct cub3d *cub, char *img_data, int line_length,
                     int x, int y, int wall_orientation, int tex_x, int tex_y)
{
    int color;
    void *tex = get_texture_image(cub, wall_orientation);
    if (tex)
        color = read_pixel_from_texture(tex, tex_x, tex_y);
    else
        color = get_texture_color(cub, wall_orientation);

    put_pixel_to_image(img_data, x, y, color, line_length);
}


static void draw_flat_pixel(char *img_data, int line_len, int x, int y, int color)
{
    put_pixel_to_image(img_data, x, y, color, line_len);
}

/* -------------------------------------------------------------------------- */
/*                     Colonne texturée sans “étirement”                       */
/* -------------------------------------------------------------------------- */

void draw_wall_column_textured(struct cub3d *cub, char *img_data, int line_len,
                               int x, int screen_h, double perpDist,
                               int floor_color, int ceiling_color, int orientation)
{
    if (!cub || !img_data) return;
    if (perpDist < 0.05) perpDist = 0.05;

    /* Hauteur théorique (avant clipping) */
    int lineHeight = (int)((double)screen_h / perpDist);
    if (lineHeight < 1) lineHeight = 1;

    /* Bornes théoriques (non clippées) */
    int drawStart_theo = -lineHeight / 2 + screen_h / 2;
    int drawEnd_theo   =  lineHeight / 2 + screen_h / 2;

    /* Clipping écran */
    int y0 = drawStart_theo; if (y0 < 0) y0 = 0;
    int y1 = drawEnd_theo;   if (y1 >= screen_h) y1 = screen_h - 1;

    /* Ciel */
    for (int y = 0; y < y0; ++y)
        draw_flat_pixel(img_data, line_len, x, y, ceiling_color);

    /* Dimensions textures (⚠️ adapte si tes textures ne sont pas carrées 64x64) */
    int texW = 64, texH = 64;

    /* texX depuis wall_x calculé dans la DDA */
    int texX = (int)(cub->wall_x * (double)texW);
    if (texX < 0) texX = 0;
    if (texX >= texW) texX = texW - 1;

    /* Flip éventuel pour uniformiser l’orientation (selon ta convention) */
    /* Ici, on retourne horizontalement pour Nord(0) et Ouest(3) */
    if (orientation == 0 || orientation == 3)
        texX = texW - 1 - texX;

    /* Avancement régulier dans la texture en partant du DEBUT THEORIQUE */
    double step   = (double)texH / (double)lineHeight;
    double texPos = (double)(y0 - drawStart_theo) * step;

    for (int y = y0; y <= y1; ++y) {
        int texY = (int)texPos;
        if (texY < 0) texY = 0;
        if (texY >= texH) texY = texH - 1;

        draw_wall_pixel(cub, img_data, line_len, x, y, orientation, texX, texY);
        texPos += step;
    }

    /* Sol */
    for (int y = y1 + 1; y < screen_h; ++y)
        draw_flat_pixel(img_data, line_len, x, y, floor_color);
}
