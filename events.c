#include "fdf.h"

int	escape_hook(t_mlx *mlx)
{
	mlx_free(mlx);
	exit(EXIT_SUCCESS);
}

int		key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_free(mlx);
		exit(0);
	}
	else if (keycode == KEY_SPACE)
	{
		map_translate(mlx, (WIN_WIDTH + PAD) / 2 - mlx->center.x,
		(WIN_HEIGHT + PAD) / 2 - mlx->center.y, 0);
	}
	else if (keycode == KEY_P)
		mlx->center.projection = !mlx->center.projection;
	else if (keycode == KEY_ARROWUP)
		mlx->center.z += 0.1;
	else if (keycode == KEY_ARROWDOWN)
		mlx->center.z -= 0.1;
    draw(mlx);
    return(0);
}

int		mouse_down_hook(int button, int x, int y, t_mlx *mlx)
{
	t_center	center;

	mlx->mouse.x = x;
	mlx->mouse.y = y;
	if (button == MOUSE_LEFT)
        mlx->mouse.clicked |= 1;
	if (button == MOUSE_MIDDLE)
        mlx->mouse.clicked |= 4;
	if (button == MOUSE_SCROLLUP || button == MOUSE_SCROLLDOWN)
	{
		center = mlx->center;
		mlx->center.x = x + PAD / 2;
		mlx->center.y = y + PAD / 2;
		if (button == MOUSE_SCROLLUP)
            map_scale(mlx, 1 + SCALE_ZOOM);
		if (button == MOUSE_SCROLLDOWN)
            map_scale(mlx, 1 - SCALE_ZOOM);
		mlx->center = center;
		draw(mlx);
	}
	return (0);
}

int		mouse_up_hook(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	if (button == 1)
        mlx->mouse.clicked ^= 1;
	if (button == 3)
        mlx->mouse.clicked ^= 4;
	return (0);
}

int		mouse_move_hook(int x, int y, t_mlx *mlx)
{
	t_mouse	mouse_point;

	mouse_point = mlx->mouse;
	if (mouse_point.clicked & 1)
	{
		map_translate(mlx, x - mouse_point.x, y - mouse_point.y, 0);
	}
	if (mouse_point.clicked & 4)
	{
		map_rotate(mlx, -(x - mouse_point.x) / 360, 'y');
		map_rotate(mlx, (y - mouse_point.y) / 360, 'x');
		//map_rotate(mlx, sqrt(pow(y - mlx->center.y, 2) + pow(x - mlx->center.x, 2)) / 360, 'z');
	}
	mouse_point.x = x;
	mouse_point.y = y;
	mlx->mouse = mouse_point;
	draw(mlx);
	return (0);
}

void	control_events(t_mlx *mlx)
{
	mlx_hook(mlx->window, EVENT_ON_KEYDOWN, NO_MASK, key_hook, mlx);
	mlx_hook(mlx->window, EVENT_ON_DESTROY, NO_MASK, escape_hook, mlx);
	mlx_hook(mlx->window, EVENT_ON_MOUSEDOWN, NO_MASK, mouse_down_hook, mlx);
	mlx_hook(mlx->window, EVENT_ON_MOUSEMOVE, NO_MASK, mouse_move_hook, mlx);
	mlx_hook(mlx->window, EVENT_ON_MOUSEUP, NO_MASK, mouse_up_hook, mlx);
	init_img(mlx);
	draw(mlx);
}
