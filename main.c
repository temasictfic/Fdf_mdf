#include "fdf.h"

void exit_with_msg(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

void mlx_free(t_mlx *mlx)
{
    if (mlx->window)
        mlx_destroy_window(mlx->mlx, mlx->window);
    while(mlx->map->height--)
    {
        while (mlx->map->lines[mlx->map->height]->width--)
            if (mlx->map->lines[mlx->map->height]->points[mlx->map->lines[mlx->map->height]->width])
                free(mlx->map->lines[mlx->map->height]->points[mlx->map->lines[mlx->map->height]->width]);
        if(mlx->map->lines[mlx->map->height]->points)
            free(mlx->map->lines[mlx->map->height]->points);
        if(mlx->map->lines[mlx->map->height])
            free(mlx->map->lines[mlx->map->height]);
    }
    if(mlx->map->lines)    
        free(mlx->map->lines);
    if (mlx->map)
        free(mlx->map);
    if (mlx)
        free(mlx); //???gereklimi
}

int main(int argc, char** argv)
{
    t_mlx *mlx;
    int y = 0;
    int x = 0;

    if (argc != 2)
        exit_with_msg(USG_ERR);
    mlx = malloc(sizeof(t_mlx));
    mlx->mlx = mlx_init();
    mlx->map = parse_map_file(argv[1]);
    //mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
    
    while(mlx->map->height > y)
    {
        x = 0;
        while (mlx->map->lines[y]->width > x)
        {
            printf("%15d", mlx->map->lines[y]->points[x]->color);
            x++;
        }
        printf("\n");
        y++;
    }
    
    //printf("SSSSSSSS");
    //init_map_transform(mlx);
    //draw(mlx);   
    //control_events(mlx);
    //mlx_loop(mlx->mlx);
    return (0);
}








/**
int main(int argc, char** argv)
{
    t_map *map;
    if (argc != 2)
    {
        perror(USG_ERR);
        exit(EXIT_FAILURE);
    }
    map = parse_map_file(argv[1]);

    int row = 0;
    //int col = 0;
    while (row < 34)
    {   
        
        col = 0;
        while(col<27)
        {
            //free(map.lines->points);
            //printf("%d  %d  %d  %d\n", map[row][col].x, map[row][col].y, map[row][col].z, map[row][col].color);
            col++;
        }
        row++;
    }
    //free(map.lines->points);
    //free(map.lines); 
    system("leaks a.out");
}**/