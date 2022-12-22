#include "fdf.h"

t_line	**increase_row_num(t_line **lines, int row)
{
	t_line **new_lines;

	new_lines = malloc(sizeof(t_line*) * (row + 1));
	ft_memcpy(new_lines, lines, row * sizeof(t_line*));  
	free(lines);
	return (new_lines);
}

t_point *fill_point(char *point_str, int row, int col)
{
    t_point *p;
    char **z_and_color;
    int i;
    
    p = malloc(sizeof(t_point));
    i = count_words(point_str, ',');
    z_and_color = split_with_num(point_str, ',', i); // #line içinde freele
    free(point_str);
    p->x = col;
    p->y = row;
    p->z = ft_atoi(z_and_color[0]);
    p->color = 0xFF8000;
    if (i == 2)
    {
        p->color = ft_atoi_hex(z_and_color[1] + 2);
        free(z_and_color[1]);
    }
    free(z_and_color[0]);
    free(z_and_color);
    return (p);
}

t_line	*parse_map_file_line(char *line, int row)
{
    t_line  *lines;
	t_point	**row_points;
	char	**row_points_strs;
	int		num;
	int		col;

	num = count_words(line, ' ');
	row_points = malloc(sizeof(t_point) * num);
	row_points_strs = split_with_num(line, ' ', num); // #line içinde freele
	col = 0;
	while (col < num)
    {
		row_points[col] = fill_point(row_points_strs[col], row, col);
        col++;
    }
    free(row_points_strs);
    lines = malloc(sizeof(t_line));
    lines->points = row_points;
    lines->width = num;
	return (lines);
}

t_map	*parse_map_file(char *fdf_file)
{
    t_map	*map;
	char	*line;
	t_line	**lines;
	int		fd;
	int		row;

	fd = open(fdf_file, O_RDONLY);
	line = get_next_line(fd);
	lines = malloc(sizeof(t_line));
	row = 0;
	while (line != NULL)
	{
        lines = increase_row_num(lines, row);
		lines[row] = parse_map_file_line(line, row);
        free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
    map = malloc(sizeof(t_map));
    map->lines = lines;
    map->height = row;
    return (map);
}
