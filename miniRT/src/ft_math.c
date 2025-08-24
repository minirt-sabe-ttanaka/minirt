#include "minirt.h"

int ft_max(int x, int y);
int ft_min(int x, int y);
int ft_abs(int x);
void   ft_swap(int *x, int *y);

int ft_max(int x, int y)
{
    if (x > y)
        return (x);
    else
        return (y);
}

int ft_min(int x, int y)
{
    if (x < y)
        return (x);
    else
        return (y);
}

int ft_abs(int x)
{
    if (x < 0)
        x *= -1;
    return (x);
}

void ft_swap(int *x, int *y)
{
    int tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;
}
