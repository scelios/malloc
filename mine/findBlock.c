#include "malloc.h"

void findBlock(size_t size,t_heap **heapSend, t_block **blockSend)
{
	t_heap *heap;
	t_heap_group group = getGroup(size);
	group = TINY;
	//!
	t_block *block;
	//printf("find Block\n");
	heap = g_heap_anchor;
	while (heap)
	{
		//printf("Heap group: %d\n", heap->group);
		block = HEAP_SHIFT(heap);
		while (block && heap->group == group)
		{
			printf("Block size: %ld\n", block->data_size);
			if (block->data_size >= size && block->freed)
			{
				*heapSend = heap;
				*blockSend = block;
				//printf("Block found %p %p\n", (void *)heap, (void *)block);
				return ;
			}
			block = block->next;
		}
		heap = heap->next;
	}
	*heapSend = NULL;
	*blockSend = NULL;
	printf("End find Block\n");
}
