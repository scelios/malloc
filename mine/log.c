#include "malloc.h"

void checkPrevNext()
{
	t_heap *heap = g_heap_anchor;
	t_block *block;
	while (heap)
	{
		ft_printf("Heap: %p size: %ld free: %ld group: %d nb block: %ld\n",(void *)heap, heap->total_size, heap->free_size, heap->group, heap->block_count);
		ft_printf("prev: %p here: %p next: %p\n", (void *)heap->prev, (void *)heap, (void *)heap->next);
		block = HEAP_SHIFT(heap);
		while (block)
		{
			ft_printf("	prev %p here: %p next %p\n", (void *)block->prev, (void *) block,(void *)block->next);
			block = block->next;
		}
		heap = heap->next;
	}
}

void loga()
{
	t_heap *heap = g_heap_anchor;
	t_block *block;
	ft_printf("log %p\n", (void *)heap);
	while (heap)
	{

		ft_printf("Heap: %p size: %ld free: %ld group: %d nb block: %ld\n",(void *)heap, heap->total_size, heap->free_size, heap->group, heap->block_count);
		block = HEAP_SHIFT(heap);
		while (block)
		{
			ft_printf("	Block: %p size: %ld free: %d\n",(void *)block, block->data_size, block->freed);
			block = block->next;
		}
		heap = heap->next;
	}
}

long showBloc(t_heap *heap)
{
	long total = 0;
	t_block *block = HEAP_SHIFT(heap);
	while (block)
	{
		if (!block->freed)
		{
			ft_printf("0x%X - 0x%X : %d bytes\n", (void *)block, (void *)block + block->data_size, block->data_size);
			total += block->data_size;
		}
		block = block->next;
	}
	return total;
}


void start_show_alloc_mem()
{
	t_heap *heap = g_heap_anchor;
	long total = 0;
	while (heap)
	{
		if (heap->group == TINY)
		{
			ft_printf("TINY : 0x%X\n", (void *)heap);
			total += showBloc(heap);
		}
		else if (heap->group == SMALL)
		{
			ft_printf("SMALL : 0x%X\n", (void *)heap);
			total += showBloc(heap);
		}
		else
		{
			ft_printf("LARGE : 0x%X\n", (void *)heap);
			total += showBloc(heap);
		}
		heap = heap->next;
	}
	ft_printf("Total : %d bytes\n", total);
}

void show_alloc_mem()
{
	pthread_mutex_lock(&g_ft_malloc_mutex);
	start_show_alloc_mem();
	pthread_mutex_unlock(&g_ft_malloc_mutex);
}
