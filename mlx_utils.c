#include "fdf.h"

int		is_on_screen(int x, int y)
{
	return (x <= WIN_WIDTH + PAD && x > 0 &&
		y <= WIN_HEIGHT + PAD && y > 0);
}

int		get_color(t_point point1, t_point point2)
{
	int color;
	t_point p;

	color = 0;
	p = point2;
	if (point1.z > point2.z)
		p = point1;
	if (p.color != DEFAULT_COLOR)
		color = p.color;
	else if (p.z <= 0)
		color = 0x3264B8;
	else if (p.z > 0 && p.z <= 10)
		color = 0x32B864;
	else if (p.z > 10 && p.z <= 20)
		color = 0x96C896;
	else if (p.z > 20 && p.z <= 50)
		color = 0xFAFAC8;
	else if (p.z > 50 && p.z <= 70)
		color = 0x966450;
	else if (p.z > 70)
		color = 0xEFEFEF;
	return (color);
}

int		max_width_index(t_line **lines, int y_last_index)
{
	int y;
	int max;
	int max_index;

	max_index = 0;
	y = 0;
	max = lines[y]->width;
	while (y < y_last_index)
	{
		if (lines[y]->width > max)
		{
			max_index = y;
			max = lines[y]->width;
		}
		y++;
	}
	return (max_index);
}

void	get_map_center(t_mlx *mlx)
{
	int		x_max;
	int		max_line_index;
	int		y_last_index;

	y_last_index = mlx->map->height - 1;
	max_line_index = max_width_index(mlx->map->lines, y_last_index);
	x_max = mlx->map->lines[max_line_index]->width;
	mlx->center.x = mlx->map->lines[max_line_index]->points[x_max - 1]->x / 2;
	mlx->center.y = mlx->map->height / 2;
}

void	init_map_transform(t_mlx *mlx)
{
	int		width;
	int		height;
	double	scale;

	get_map_center(mlx);
	width = (WIN_WIDTH + PAD) / 2;
	height = (WIN_HEIGHT + PAD) / 2;
	if (mlx->center.x == 0)
		mlx->center.x = 10;
	mlx->mouse.clicked = 0;
	mlx->center.projection = 1;
    mlx->center.z = 1;
	scale = (width - 600) / (mlx->center.x);
	map_translate(mlx, width - mlx->center.x, height - mlx->center.y, 0);
	map_scale(mlx, scale);
}