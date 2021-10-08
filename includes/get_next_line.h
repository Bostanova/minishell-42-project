#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
size_t	gnl_len(const char *s);
char	*gnl_strjoin(const char *s1, const char *s2);
void	*gnl_memcpy(void *dst, const void *src, size_t n);
void	*gnl_memmove(void *dst, const void *src, size_t len);

#endif