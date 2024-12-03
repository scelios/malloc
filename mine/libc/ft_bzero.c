#include "../malloc.h"

void	ft_bzero(void *s, size_t n)
{
	char *str;

	str = (char *)s;
	while (n--)
		str[n] = 0;
}
