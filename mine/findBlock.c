#include "malloc.h"

void findBlock(size_t size,t_heap **heapSend, t_block **blockSend)
{
	t_heap *heap;
	t_heap_group group = getGroup(size);
	t_block *block;
	heap = g_heap_anchor;
	while (heap)
	{
		block = HEAP_SHIFT(heap);
		while (block && heap->group == group)
		{
			if (block->data_size >= size && block->freed)
			{
				*heapSend = heap;
				*blockSend = block;
				return ;
			}
			block = block->next;
		}
		heap = heap->next;
	}
	*heapSend = NULL;
	*blockSend = NULL;
}
