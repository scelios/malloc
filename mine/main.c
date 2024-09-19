#include "malloc.h"
#include <strings.h>
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}



void	*start_malloc(size_t size)
{
	t_heap	*heap;
	t_block	*block;
	void	*res = NULL;

	if (!size)
		return (NULL);
	size = (size + 15) & ~15;
	printf("start_malloc\n");
	if((block = find_block(size)) != NULL)
	{
		return (block);
	}
	else
		return create_heap(size);
	printf("End malloc\n");

	return (res);
}

void	*alloc(size_t size)
{
	void *res;
	// pthread_mutex_lock(&g_ft_malloc_mutex);
	printf("malloc\n");
	if ((res = start_malloc(size)))
		ft_memset(res, 0xaa, size);
	// pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (res);
}

void fctn(char *test, char *p)
{
	int i = 0;
	while (*p)
	{
		test[i] = *p;
		i++;
		p++;
	}
	test[i] = '\0';

}
int main()
{
	int length = 50;
	char *test = alloc(length);
	printf("\n\n");

	char *test2 = alloc(length);
	char *test3 = alloc(length);
	// char *test4;
	printf("\n\n");
	fctn(test, "abcdef");
	fctn(test2, "1234567890");
	fctn(test3, "ghijkl");
	// fctn(test4, "ghijkl");

	printf("test: %s\n", test);
	printf("test2: %s\n", test2);
	// printf("test3: %s\n", test3);

	// printf("test4: %s\n", test4);
	// char *test = (char *) mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	// if (test == MAP_FAILED)
	// 	return (0);

	// int i = -1;

	// while (++i < length)
	// {
	// 	test[i] = 'a' + i;
	// 	write(0, &test[i],1);
	// }
	// write(0, "\n",1);
	// i=-1;
	// while (++i < length)
	// {
	// 	write(0, &test[i],1);
	// }

	return 0;
}