#include "../libft.h"
#include <stdarg.h>

char *ft_argv_strjoin(int count, ...) {
    va_list list;
    int i = 0;
    char *joined = "";

    va_start(list, count);
    while (i < count)
    {
        ft_unleak_strjoin(&joined, va_arg(list, char *));
        i++;
    }
    va_end(list);
    return (joined);
}