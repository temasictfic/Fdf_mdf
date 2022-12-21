#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*ft_read(int fd, char *str);
char	*ft_get_line(char *str);
char	*ft_get_rest(char *str);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, void *src, size_t n);
size_t	ft_strlen(char *str);
int		ft_has_newline(char *str);

#endif