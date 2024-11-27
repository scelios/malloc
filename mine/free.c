#include "malloc.h"

t_bool allFree(t_heap *heap)
{
	t_block *block;

	block = HEAP_SHIFT(heap);
	while (block)
	{
		if (block->freed == FALSE)
			return (FALSE);
		block = block->next;
	}
	return (TRUE);
}

void	start_free(void *ptr)
{
	t_heap	*heap;
	t_block	*block;
	t_block	*ret;
	t_block	*tmp;
	int		blockFreed = 0;
	t_bool	found = FALSE;
	size_t size = 0;
	heap = g_heap_anchor;
	searchPtr(ptr, &heap, &block);
	if (block != NULL && heap != NULL)
	{
		block->freed = TRUE;
		heap->free_size += block->data_size;
		if (allFree(heap) == TRUE)
		{
			if (heap->prev)
				heap->prev->next = heap->next;
			if (heap->next)
				heap->next->prev = heap->prev;
			if (heap == g_heap_anchor)
				g_heap_anchor = heap->next;
			munmap(heap, heap->total_size);
			return;
		}
		ret = block;
		while (ret->prev && ret->prev->freed == TRUE)
		{
			ret = ret->prev;
			size += ret->data_size + sizeof(t_block);
			blockFreed++;
		}
		if (blockFreed > 0)
		{
			ret->next = block->next;
			if (block->next)
				block->next->prev = ret;
			tmp = ret;
			ret = block;
			block = tmp;
			block->data_size += size;
			
		}
		size = 0;
		while(ret->next && ret->next->freed == TRUE)
		{
			found = TRUE;
			ret = ret->next;
			blockFreed++;
			size += ret->data_size + sizeof(t_block);

		}
		if (found == TRUE)
		{
			ret->prev = block;
			block->next = ret->next;
			if (ret->next)
				ret->next->prev = block;
			block->data_size += size;
		}
		heap->block_count -= blockFreed;
	}
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_ft_malloc_mutex);
	start_free(ptr);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
}