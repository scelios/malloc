#include "malloc.h"

void*start_realloc(void *ptr, size_t size)
{
	t_heap	*heap;
	t_block	*block;
	void	*new_ptr;

	if (!ptr)
		return (start_malloc(size));
	else if (size == 0)
	{
		start_free(ptr);
		return (NULL);
	}
	heap = g_heap_anchor;
	searchPtr(ptr, &heap, &block);
	if (!heap || !block)
		return (NULL);
	else if (size == block->data_size)
		return (ptr);
	new_ptr = start_malloc(size);
	ft_memmove(new_ptr, ptr, block->data_size > size ? size : block->data_size);
	start_free(ptr);
	return (new_ptr);
}

void*realloc(void *ptr, size_t size)
{
	void *res;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	res = start_realloc(ptr, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (res);
}
