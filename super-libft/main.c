#include "libft.h"
#include "stdio.h"

int main(void)
{
    int a = 10;
    char *salut = "je vous baize";

    ft_printf("%s\n", ft_substr(salut, 0 , 10));
    printf("%p\n", &a);

    return (0);
}