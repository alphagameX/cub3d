#include "../libft.h"

void ft_unleak_strjoin(char **dst, char *src) {
    char *tmp = ft_strdup((const char *)*dst);
    if(**dst)
        free(*dst);
    *dst = ft_strjoin(tmp , src);
    free(tmp);
}
