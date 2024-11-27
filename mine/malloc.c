#include "malloc.h"


void	*start_malloc(size_t size)
{
	t_heap	*heap = NULL;
	t_block	*block = NULL;

	if (!size)
		return (NULL);
	size = (size + 15) & ~15 ;
	findBlock(size, &heap, &block);
	if( block != NULL)
	{
		divideBlock(size,heap, block);
	}
	else
	{
		createHeap(size,&heap, &block);
		if (heap == NULL)
		{
			return (NULL);
		}
		divideBlock(size,heap, block);
	}
	return (BLOCK_SHIFT(block));
}

void	*malloc(size_t size)
{
	void *res;
	pthread_mutex_lock(&g_ft_malloc_mutex);

	res = start_malloc(size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (res);
}

