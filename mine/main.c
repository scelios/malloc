#include "malloc.h"
#include <string.h>

void fctn(char *test, char *str)
{
	int i = -1;
	while (str[++i])
	{
		test[i] = str[i];
	}
	test[i] = 0;
}

#define M 1024 * 1024



// int	main(void)
// {
// 	malloc(10);
// 	malloc(16);
// 	malloc(1024);
// 	malloc(1024 * 32);
// 	malloc(1024 * 1024);
// 	malloc(1024 * 1024 * 16);
// 	malloc(1024 * 1024 * 128);
// 	show_alloc_mem();
// 	// loga();
// 	return (0);
// }
#define M 1024 * 1024

void	print(char *s)
{
	write(1, s, strlen(s));
}

int	main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		write(1,addr,1);
		free(addr);
		i++;
	}
	return (0);
}
