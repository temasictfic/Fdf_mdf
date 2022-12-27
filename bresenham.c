#include "fdf.h"

void iso(t_point *p, t_mlx *mlx)
{
    double angle;

    angle = M_PI * 30 / 180;
    p->x = (p->x - p->y) * cos(angle);
    p->y = (-p->z * mlx->center.z) + (p->x + p->y) * sin(angle);
}

void apply_projection(t_point *p1, t_point *p2, t_mlx *mlx, int projection)
{
    if (projection)
    {
        iso(p1, mlx);
        iso(p2, mlx);
    }
}

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    //char *img_addr;
    int i;
    //int x_off;
    //int y_off;

    //x_off = x + WIN_WIDTH/2;
    //y_off = y + WIN_HEIGHT/2;
    if(x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
    {
        i = (y * mlx->line_length + (x * mlx->bits_per_pixel / 8));
        mlx->img_addr[i] = color;
        mlx->img_addr[++i] = color >> 8;
        mlx->img_addr[++i] = color >> 16;


        //*(unsigned int *)img_addr = color;
    }
}

void bresenham(t_point *p1, t_point *p2, t_mlx *mlx)
{
    int dx;
    int dy;
    int err;
    int e2;

    apply_projection(p1, p2, mlx, mlx->center.projection);
    dx = abs(p1->x - p2->x);
    dy = abs(p1->y - p2->y);
    err = -dy / 2;
    if (dx > dy)
        err = dx / 2;
    while (1)
    {
        put_pixel(mlx, p1->x, p1->y, get_color(p1, p2));
        if (p1->x == p2->x && p1->y == p2->y)
            break;
        e2 = err;
        if(e2 > -dx)
        {
            err -= dy;
            p1->x += (p1->x < p2->x) - (p1->x > p2->x);
        }
        if(e2 < dy)
        {
            err += dx;
            p1->y = (p1->y < p2->y) - (p1->y > p2->y);
        }
    }
}