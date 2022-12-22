#include "fdf.h"
// free tmp?
void matrice_multiply(t_matrice *m, t_mlx *mlx)
{
    t_point *p;
    t_point *tmp;
    int     x;
    int     y;

    tmp = malloc(sizeof(t_point));
    y = 0;
    while (y < mlx->map->height)
    {
        x = 0;
        while (x < (mlx->map->lines[y]->width))
        {
            p = mlx->map->lines[y]->points[x];
            p->x -= mlx->center.x;
            p->y -= mlx->center.y;
            tmp->x = p->x * m->a[0] + p->y * m->a[1] + p->z * m->a[2] + m->a[3] * 1;
            tmp->y = p->x * m->b[0] + p->y * m->b[1] + p->z * m->b[2] + m->b[3] * 1;
            tmp->z = p->x * m->c[0] + p->y * m->c[1] + p->z * m->c[2] + m->c[3] * 1;
            tmp->x += mlx->center.x;
            tmp->y += mlx->center.y;
            p->x = tmp->x;
            p->y = tmp->y;
            p->z = tmp->z;
            x++;
        }
        y++;
    }
    free(tmp);
}

/*
tmp->x = p->x * cos(angle) + p->z * sin(angle);
tmp->y = p->y * 1;
tmp->z = -p->x * sin(angle) + p-z * cos(angle);
p->x = tmp->x;
p->y = tmp->y;
p->z = tmp->z;

tmp->x = p->x * cos(angle) - p->y * sin(angle);
tmp->y = p->x * sin(angle) + p->y * cos(angle);
tmp->z =  + p-z * 1;
p->x = tmp->x;
p->y = tmp->y;
p->z = tmp->z;

*/

/*
        ---Translate matrice---    

    {{1,     0,     0,       x},
     {0,     1,     0,       y},
     {0,     0,     1,       z},
     {0,     0,     0,       1}};

*/

void map_translate (t_mlx *mlx, double x, double y, double z)
{
    t_matrice *transition_m;

    transition_m = malloc(sizeof(t_matrice));
    transition_m->a[0] = 1;
    transition_m->b[1] = 1;
    transition_m->c[2] = 1;
    transition_m->a[3] = x;
    transition_m->b[3] = y;
    transition_m->c[3] = z;
    transition_m->d[3] = 1;
    matrice_multiply(transition_m, mlx);
    get_map_center(mlx);
    free(transition_m);
}


/*
        ---Scale matrice---    

    {{scale, 0,     0,       0},
     {0,     scale, 0,       0},
     {0,     0,     scale,   0},
     {0,     0,     0,       1}};

*/

void map_scale(t_mlx *mlx, double scale)
{
    t_matrice *scale_m;

    scale_m = malloc(sizeof(t_matrice));

    scale_m->a[0] = scale;
    scale_m->b[1] = scale;
    scale_m->c[2] = scale;
    scale_m->d[3] = 1;
    matrice_multiply(scale_m, mlx);
    free(scale_m);
}
/*
        ---Rotate x-axis---    

    {{1,     0,     0,       0},
     {0,     cos_v, -sin_v,  0},
     {0,     sin_v, cos_v,   0},
     {0,     0,     0,       1}};

        ---Rotate y-axis--- 

    {{cos_v,     0,     sin_v,   0},
     {0,         1,     0,       0},
     {-sin_v,    0,     cos_v,   0},
     {0,         0,     0,       1}};

             ---Rotate z-axis--- 

    {{cos_v,     -sin_v,    0,   0},
     {sin_v,     cos_v,     0,   0},
     {0,         0,         1,   0},
     {0,         0,         0,   1}};

*/

void map_rotate(t_mlx *mlx, double angle, char axis)
{
    double  cos_v;
    double  sin_v;
    t_matrice   *rotate_m;
    
    rotate_m = malloc(sizeof(t_matrice));
    cos_v = cos(angle);
    sin_v = sin(angle);

    rotate_m->a[0] = cos_v;
    rotate_m->b[1] = cos_v;
    rotate_m->c[2] = cos_v;
    rotate_m->d[3] = 1;

    if (axis == 'x')
    {
        rotate_m->a[0] = 1;
        rotate_m->b[2] = -sin_v;
        rotate_m->c[1] = sin_v;
    }
    else if (axis == 'y')
    {
        rotate_m->a[2] = sin_v;
        rotate_m->b[1] = 1;
        rotate_m->c[0] = -sin_v;
    }
    else if (axis == 'z')
    {
        rotate_m->a[1] = -sin_v;
        rotate_m->b[0] = sin_v;
        rotate_m->c[2] = 1;
    }
    matrice_multiply(rotate_m, mlx);
    free(rotate_m);
}