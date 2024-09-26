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
	t_heap	*heap = NULL;
	t_block	*block = NULL;


	if (!size)
		return (NULL);
	//printf("start_malloc %d\n",size);
	
	// size += sizeof(t_block) + sizeof(t_heap);
	size = (size + 15) & ~15 ;
	//printf("start_malloc %d\n",size);
	findBlock(size, &heap, &block);
	if( block != NULL)
	{
		divideBlock(size,heap, block);
	}
	else
	{
		//printf("Block not found\n");
		createHeap(size,&heap, &block);
		//printf("Heap %p\n", (void *)heap);

		if (heap == NULL)
			return (NULL);
		divideBlock(size,heap, block);
	}
	//printf("End malloc\n");
	return (BLOCK_SHIFT(block));
}

void	*alloc(size_t size)
{
	void *res;
	// pthread_mutex_lock(&g_ft_malloc_mutex);

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
	int length = 1900;
	//printf("%d %d\n", sizeof(t_heap), sizeof(t_block));
	// int i = -1;
	// char *testi[1000];
	// while (++i < 1000)
	// {
	// 	testi[i] = alloc(length);
	// }
	char *test = alloc(length);
	//printf("\n\n");

	char *test2 = alloc(length);
	char *test3 = alloc(148);

	// char *test3 = alloc(length);
	// char *test4;
	//printf("\n\n");
	fctn(test, "abcdef");
	fctn(test2, "1234567890");
	// fctn(test3, "ghijkl");
	// fctn(test4, "ghijkl");

	printf("test: %s %p\n", test, (void *)test);

	printf("test2: %s %p\n", test2, (void *)test2);

	//printf("adress %p\n", (void *)test2 - (void *)test  - sizeof(t_block) );
	// printf("test3: %s %p\n", test3, (void *)test3);
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