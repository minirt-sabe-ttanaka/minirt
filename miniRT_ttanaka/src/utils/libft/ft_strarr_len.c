#include "core/utils/libft.h"

size_t ft_strarr_len(char **strarr)
{
    size_t i;

    i = 0;
    while (strarr[i])
    {
        i++;
    }
    return (i);
}