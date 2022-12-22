#include "fdf.h"

void	destroy_img(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img_addr = NULL; //gerekli mi?
	mlx->img = NULL; //gerekli mi?
}

void	draw(t_mlx *mlx)
{
	int	x;
	int	y;

	
	//init_img(mlx);
	y = 0;
	while (mlx->map->height > y)
	{
		x = 0;
		while (mlx->map->lines[y]->width > x)
		{
			if ((x + 1) < mlx->map->lines[y]->width)
				bresenham(*(mlx->map->lines[y]->points[x]), *(mlx->map->lines[y]->points[x + 1]), mlx);
			if ((y + 1) < mlx->map->height)
				bresenham(*(mlx->map->lines[y]->points[x]), *(mlx->map->lines[y + 1]->points[x]), mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
	destroy_img(mlx);

}