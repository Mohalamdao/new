/ Fonction appelée quand une touche est pressée
int key_press(int keycode, t_cub3d *cub)
{
    if (keycode == KEY_W)
        cub->keys.w = 1;
    else if (keycode == KEY_S)
        cub->keys.s = 1;
    else if (keycode == KEY_A)
        cub->keys.a = 1;
    else if (keycode == KEY_D)
        cub->keys.d = 1;
    else if (keycode == KEY_LEFT)
        cub->keys.left = 1;
    else if (keycode == KEY_RIGHT)
        cub->keys.right = 1;
    else if (keycode == KEY_ESC)
        cub->keys.esc = 1;
    return (0);
}

// Fonction appelée quand une touche est relâchée
int key_release(int keycode, t_cub3d *cub)
{
    if (keycode == KEY_W)
        cub->keys.w = 0;
    else if (keycode == KEY_S)
        cub->keys.s = 0;
    else if (keycode == KEY_A)
        cub->keys.a = 0;
    else if (keycode == KEY_D)
        cub->keys.d = 0;
    else if (keycode == KEY_LEFT)
        cub->keys.left = 0;
    else if (keycode == KEY_RIGHT)
        cub->keys.right = 0;
    else if (keycode == KEY_ESC)
        cub->keys.esc = 0;
    return (0);
}

// Fonction pour traiter les mouvements selon l'état des touches
void handle_movement(t_cub3d *cub)
{
    // Mouvement avant/arrière
    if (cub->keys.w)
        move_forward(cub);
    if (cub->keys.s)
        move_backward(cub);
    
    // Mouvement latéral (strafe)
    if (cub->keys.a)
        move_left(cub);
    if (cub->keys.d)
        move_right(cub);
    
    // Rotation
    if (cub->keys.left)
        rotate_left(cub);
    if (cub->keys.right)
        rotate_right(cub);
    
    // Quitter
    if (cub->keys.esc)
        exit_cub(cub);
}

// Fonction principale de la boucle de jeu
int cub_loop(t_cub3d *cub)
{
    // Traiter les mouvements selon l'état des touches
    handle_movement(cub);
    
    // Effectuer le raycasting et le rendu
    render_frame(cub);
    
    return (0);
}

// Fonction d'initialisation
void init_cub(t_cub3d *cub)
{
    // Initialiser MLX
    cub->mlx = mlx_init();
    cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3d");
    
    // Initialiser l'état des touches à 0
    ft_memset(&cub->keys, 0, sizeof(t_keys));
    
    // Enregistrer les fonctions de callback
    mlx_hook(cub->win, 2, 1L<<0, key_press, cub);      // KeyPress
    mlx_hook(cub->win, 3, 1L<<1, key_release, cub);    // KeyRelease
    mlx_hook(cub->win, 17, 1L<<17, close_window, cub); // DestroyNotify
    
    // Boucle principale
    mlx_loop_hook(cub->mlx, cub_loop, cub);
    mlx_loop(cub->mlx);
}

// Exemples de fonctions de mouvement
void move_forward(t_cub3d *cub)
{
    double new_x = cub->player.x + cub->player.dir_x * MOVE_SPEED;
    double new_y = cub->player.y + cub->player.dir_y * MOVE_SPEED;
    
    // Vérifier les collisions avant de bouger
    if (cub->map[(int)new_y][(int)cub->player.x] == '0')
        cub->player.y = new_y;
    if (cub->map[(int)cub->player.y][(int)new_x] == '0')
        cub->player.x = new_x;
}

void rotate_left(t_cub3d *cub)
{
    double old_dir_x = cub->player.dir_x;
    double old_plane_x = cub->player.plane_x;
    
    cub->player.dir_x = cub->player.dir_x * cos(ROT_SPEED) - cub->player.dir_y * sin(ROT_SPEED);
    cub->player.dir_y = old_dir_x * sin(ROT_SPEED) + cub->player.dir_y * cos(ROT_SPEED);
    cub->player.plane_x = cub->player.plane_x * cos(ROT_SPEED) - cub->player.plane_y * sin(ROT_SPEED);
    cub->player.plane_y = old_plane_x * sin(ROT_SPEED) + cub->player.plane_y * cos(ROT_SPEED);
}
