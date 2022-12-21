#include "fdf.h"

t_point	set_point(int x, int y, int z)
{
	t_point	p;

	p.x = x;
	p.y = y;
    p.z = z;
	return (p);
}

void	init_img(t_mlx *mlx)
{
	mlx->img = mlx_new_image(mlx->mlx, 1920, 1080);
	if (!mlx->img)
		exit_program(IMG_ERR);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->img_addr)
		exit_program(IMG_ERR);
}

t_mlx *init_mlx(t_map *map)
{
    t_mlx *mlx;
    int width;
    int height;
    double scale;

    mlx = malloc(sizeof(t_mlx));
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
		exit_program(MLX_ERR);
    mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
    if (!mlx->window)
		exit_program(MLX_ERR);
    mlx->img = NULL;
    mlx->img_addr = NULL;
    //mlx->angle = M_PI * 30 / 180;
    //mlx->projection = 1;
    //mlx->onclick = 0;
    mlx->map = map;
    get_map_center(mlx);
    width = (WIN_WIDTH + PAD) / 2;
    height = (WIN_HEIGHT + PAD) / 2;
    if (mlx->center.x == 0)
        mlx->center.x = 10;
    mlx->mouse.color = 0;
    scale = (width - 600) / mlx->center.x;
    map_translate(mlx, width - mlx->center.x, height - mlx->center.y, mlx->center.z);
    map_scale(mlx, scale);

    //mlx->map->zoom = WIN_HEIGHT / (mlx->map->width + mlx->map->height);
    //mlx->map->color = DEFAULT_COLOR;
    //mlx->offsets->x = WIN_WIDTH / 2;
    //mlx->offsets->y = WIN_HEIGHT / 2;
    //mlx->offsets->z = 1;
}