CC = cc
CFLAGS = -Wall -Wextra -Werror -g -ggdb -fsanitize=address #-fno-omit-frame-pointer -fsanitize=undefined 
RM = rm -f
#-O3 -Ofast -flto -march=native
NAME = fdf
LIBS = -Lminilibx_macos -lmlx -lm -framework OpenGL -framework AppKit
SRCS = bresenham.c events.c draw.c init.c main.c matrices.c mlx_utils.c parse_map.c utils*.c gnl/*.c


all: ${NAME}

bonus: ${NAME}

${NAME}:
	${CC} ${CFLAGS} ${SRCS} ${LIBS} -o ${NAME}

clean:

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re