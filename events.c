#include "fdf.h"

int	escape_hook(t_mlx *mlx)
{
	env_free(mlx);
	exit(EXIT_SUCCESS);
}

int		key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		env_free(mlx);
		exit(0);
	}
	else if (keycode == KEY_SPACE)
	{
		map_translate(mlx, (WIN_WIDTH + PAD) / 2 - mlx->center.x,
		(WIN_HEIGHT + PAD) / 2 - mlx->center.y, 0);
	}
    draw(mlx);
    return(0);
}

int		mouse_down_hook(int button, int x, int y, t_mlx *mlx)
{
	t_point	point;

	mlx->mouse.x = x;
	mlx->mouse.y = y;
	if (button == 1)
        mlx->mouse.color = (int)mlx->mouse.color | 1;
	if (button == 3)
        mlx->mouse.color = (int)mlx->mouse.color | 4;
	if (button == 4 || button == 5)
	{
		point = mlx->center;
		mlx->center.x = x + 50;
		mlx->center.y = y + 50;
		if (button == 4)
            map_scale(mlx, 1 + SCALE_ZOOM);
		if (button == 5)
            map_scale(mlx, 1 - SCALE_ZOOM);
		mlx->center = point;
		draw(mlx);
	}
	return (0);
}

int		mouse_up_hook(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	if (button == 1)
        mlx->mouse.color = (int)mlx->mouse.color ^ 1;
	if (button == 3)
        mlx->mouse.color = (int)mlx->mouse.color ^ 4;
	return (0);
}

int		mouse_move_hook(int x, int y, t_mlx *mlx)
{
	t_point	mouse_point;

	mouse_point = mlx->mouse;
	if (((int)mouse_point.color & 1))
	{
		map_translate(mlx, x - mouse_point.x, y - mouse_point.y, 0);
	}
	if (((int)mouse_point.color & 4))
	{
		map_rotate(mlx, -(x - mouse_point.x) / 360, 'y');
		map_rotate(mlx, (y - mouse_point.y) / 360, 'x');
	}
	mouse_point.x = x;
	mouse_point.y = y;
	mlx->mouse = mouse_point;
	draw(mlx);
	return (0);
}

