#ifndef FDF_H
# define FDF_H

#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"
#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

# define PAD 100
# define SCALE_ZOOM 0.1

#ifndef WIN_WIDTH
 #define WIN_WIDTH 1280
#endif

#ifndef WIN_HEIGHT
 #define WIN_HEIGHT 720
#endif
// Bisque
#ifndef COLOR_LOW
 #define COLOR_LOW 0xffe6cc
#endif
// Orange
#ifndef COLOR_HIGH
 #define COLOR_HIGH 0xff8000
#endif

#define DEFAULT_COLOR 0xff8000

#define MLX_ERR "Mlx Error!"
#define IMG_ERR "Image Initialization Error!"
#define USG_ERR "Usage: ./fdf <.fdf map file>"
#define OPEN_MAP_ERR "Failed to open map!"
#define INIT_MAP_ERR "Failed to initialize map!"
#define READ_MAP_ERR "Failed to read map!"
#define ALLOC_ERR "Failed to allocate memory!"

#define EVENT_ON_KEYDOWN 2
#define EVENT_ON_KEYUP   3
#define EVENT_ON_MOUSEDOWN 4
#define EVENT_ON_MOUSEUP 5
#define EVENT_ON_MOUSEMOVE 6
#define EVENT_ON_DESTROY 17
#define NO_MASK 0

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 3
#define MOUSE_SCROLLUP 4
#define MOUSE_SCROLLDOWN 5

#define KEY_ESC 53
# define KEY_SPACE 49
// Offset X +-
#define KEY_ARROWLEFT 123
#define KEY_ARROWRIGHT 124
// Offset Y +-
#define KEY_ARROWUP 126
#define KEY_ARROWDOWN 125
// Zoom +-
#define KEY_P 35
#define KEY_I 34
#define KEY_O 31
// Raise Z, Lower Z
#define KEY_W 13
#define KEY_S 1
// Angle +-
#define KEY_A 0
#define KEY_D 2
// Projections paralel, iso, conic
#define KEY_ONE 18
#define KEY_TWO 19
#define KEY_THREE 20

typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
}   t_point;

typedef struct s_mouse
{
    int x;
    int y;
    int clicked;
}   t_mouse;

typedef struct s_center
{
    int x;
    int y;
    int z;
    int projection;
    //double angle;
}   t_center;

typedef struct	s_line {
	t_point	**points;
	int		width;
}				t_line;

typedef struct	s_map {
	t_line	**lines;
	int		height;
}				t_map;

typedef struct s_mlx
{
    void    *mlx;
    void    *window;
    void    *img;
    void    *img_addr;
    t_map   *map;
    t_mouse mouse;
    t_center center;
    int bits_per_pixel;
    int line_length;
    int endian;
}       t_mlx;

typedef struct	s_matrice {

	double a[4];
	double b[4];
	double c[4];
	double d[4];
}               t_matrice;

char	**split_with_num(char const *str, char c, int num);
unsigned int	count_words(const char *str, char sep);
char	*ft_toupper(char *str);
long int	ft_atoi(const char *str);
unsigned int	ft_atoi_hex(char *str);

t_map	*parse_map_file(char *fdf_file);
int		is_on_screen(int x, int y);
int		get_color(t_point *point1, t_point *point2);
void	get_map_center(t_mlx *mlx);
void exit_with_msg(char *str);

void map_translate (t_mlx *mlx, double x, double y, double z);
void	draw(t_mlx *mlx);
void map_scale(t_mlx *mlx, double scale);
void map_rotate(t_mlx *mlx, double angle, char axis);
void	destroy_img(t_mlx *mlx);
void	init_img(t_mlx *mlx);
void bresenham(t_point *p1, t_point *p2, t_mlx *mlx);
void	control_events(t_mlx *mlx);
void mlx_free(t_mlx *mlx);
//t_mlx *init_mlx(t_map *map);
void	init_map_transform(t_mlx *mlx);

/*
// Initialization
t_map	*init_map(void);
t_mlx	*init_mlx(t_map *map);
// Read map & Fill lines;
void read_map(int fd, t_map *map);
void fill_lines(char **lines, int width, t_map *map);
// Projections
void apply_conic(t_p *p1, t_p *p2, t_z *z, t_mlx *mlx);
void apply_iso(t_p *p1, t_p *p2, t_z *z, t_mlx *mlx);
// Draw
void bresenham(t_p p1, t_p p2, t_mlx *mlx);
void	draw(t_mlx *mlx);
// Utils
int err_calc(t_p *delta);
long int	ft_atoi(const char *str);
char	**split_with_num(char const *str, char c, int num);
// Events
int	handle_key(int keycode, void *param);
int	escape(void *param);
int	mouse(int keycode, int x, int y, void *param);
int	mouse_move(int x, int y, void *param);
int	mouse_release(int keycode, int x, int y, void *param);
*/

#endif