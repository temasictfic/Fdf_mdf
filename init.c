#include "fdf.h"

void init_img(t_mlx *mlx)
{
    mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    mlx->img_addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel), &(mlx->line_length), &(mlx->endian));
    if (!mlx->img_addr)
		exit_with_msg(IMG_ERR);
}

void	init_map_transform(t_mlx *mlx)
{
	int		width;
	int		height;
	double	scale;

	get_map_center(mlx);
	width = WIN_WIDTH / 2;
	height = WIN_HEIGHT / 2;
	if (mlx->center.x == 0)
		mlx->center.x = 10;
	mlx->mouse.clicked = 0;
	mlx->mouse.x = mlx->center.x;
	mlx->mouse.y =  mlx->center.y;
	mlx->center.projection = 1;
    mlx->center.z = 1;
	scale = (width - 600) / (mlx->center.x);
	map_translate(mlx, width - mlx->center.x, height - mlx->center.y, 0);
	map_scale(mlx, scale);
}

t_mlx   *init_mlx(t_map *map)
{
    t_mlx *mlx;

    mlx = malloc(sizeof(t_mlx));

    mlx->mlx = mlx_init();

    mlx->window=mlx_new_window(mlx->mlx,WIN_WIDTH, WIN_HEIGHT, "Fdf");

    init_img(mlx);

    mlx->map = map;

    init_map_transform(mlx);

    return(mlx);
    
}

/*#include "fdf.h"

t_mlx *init_mlx(t_map *map)
{
    t_mlx *mlx;
    int width;
    int height;
    double scale;

    mlx = malloc(sizeof(t_mlx));
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
		  exit_with_msg(MLX_ERR);
    mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
    if (!mlx->window)
		  exit_with_msg(MLX_ERR);
    mlx->map = map;
    mlx->img = NULL;
    mlx->img_addr = NULL;
    get_map_center(mlx);
    mlx->center.projection = 1;
    mlx->center.z = 1;
    mlx->mouse.clicked = 0;
    width = (WIN_WIDTH + PAD) / 2;
    height = (WIN_HEIGHT + PAD) / 2;
    if (mlx->center.x == 0)
        mlx->center.x = 10;
    scale = (width - 600) / mlx->center.x;
    map_translate(mlx, width - mlx->center.x, height - mlx->center.y, 0);
    map_scale(mlx, scale);

    //mlx->map->zoom = WIN_HEIGHT / (mlx->map->width + mlx->map->height);
    //mlx->map->color = DEFAULT_COLOR;
    //mlx->offsets->x = WIN_WIDTH / 2;
    //mlx->offsets->y = WIN_HEIGHT / 2;
    //mlx->offsets->z = 1;
    return(mlx);
}*/