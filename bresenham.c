#include "fdf.h"

void iso(t_point *p, t_mlx *mlx)
{
    double angle;

    angle = M_PI * 30 / 180;
    p->x = (p->x - p->y) * cos(angle);
    p->y = (-p->z * mlx->center.z) + (p->x + p->y) * sin(angle);
}

void apply_projection(t_point *p1, t_point *p2, t_mlx *mlx, int flag)
{
    if (flag)
    {
        iso(p1, mlx);
        iso(p2, mlx);
    }

}

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char *img_addr;
    if(is_on_screen(x, y))
    {
        img_addr = mlx->img_addr + y * mlx->line_length + x * (mlx->bits_per_pixel / 8);
        *(unsigned int *)img_addr = color;
    }
}

void bresenham(t_point p1, t_point p2, t_mlx *mlx)
{
    int dx;
    int dy;
    int err;
    int e2;

    apply_projection(&p1, &p2, mlx, mlx->center.projection);
    dx = fabs(p2.x-p1.x);
    dy = -fabs(p2.y-p1.y);
    err = dx + dy;
    while (1)
    {
        put_pixel(mlx, p1.x, p1.y, get_color(p1, p2));
        if (p1.x == p2.x && p1.y == p2.y)
            break;
        e2 = 2 * err;
        if(e2 >= dy)
        {
            err += dy;
            p1.x += (p1.x < p2.x) - (p1.x > p2.x);
        }
        if(e2 <= dx)
        {
            err += dx;
            p1.y = (p1.y < p2.y) - (p1.y > p2.y);
        }
    }
}