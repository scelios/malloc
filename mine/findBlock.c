#include "malloc.h"

t_heap_group get_group(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY);
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}

t_block *cut_block_from_heap(t_heap *heap, t_block *block, size_t size)
{
	t_block *left_block;
	t_block *right_block;
	printf("block adress in cut: %p Previous: %p Next: %p\n", block, block->prev, block->next);

	if (block->next || block->next == (t_block*)0x1 || block->next != (t_block*)0xaaaaaaaaaaaaaaaa )
	{
		printf("Block is the last one\n");
		block->next = NULL;
	}
	if (block->prev || block->prev == (t_block*)0x1|| block->prev != (t_block*)0xaaaaaaaaaaaaaaaa)
	{
		printf("Block is the first one\n");
		block->prev = NULL;
	}
	if (block->data_size - size > sizeof(t_block) + 16) // will create a new block if there is enough space for 2 blocks
	{
		heap->block_count++;
		left_block = block;
		left_block->data_size = size;
		left_block->freed = FALSE;
		right_block = (t_block *)((void *)block + sizeof(t_block) + size);
		right_block->data_size = block->data_size - size - sizeof(t_block);
		right_block->freed = TRUE;
		right_block->next = block->next;
		left_block->next = right_block;
		if (block->next)
			block->next->prev = right_block;
		right_block->prev = left_block;
		heap->free_size -= sizeof(t_block) + left_block->data_size;
		block = right_block;
		// printf("Left block created, freed %u\n", left_block->freed);
		// printf("Adress:\n left: %p\nright: %p\n", left_block, right_block);
		// printf("Next left: %p\nNext right: %p %p\n", left_block->next, right_block->next,block->next);
		printf("Block adress size: %p %p   !!!!!!!!!!\n", (void *) left_block->data_size,(void *) right_block->data_size);

		return BLOCK_SHIFT(left_block);

	}
	block->freed = FALSE;
	heap->free_size -= sizeof(t_block) + block->data_size;
	printf("cut_block_from_heap,  Block freed: %u\n", block->freed);
	printf("Block adress size: %p    !!!!!!!!!!\n", (void *) block->data_size);

	return BLOCK_SHIFT(block);
}

t_block	*find_block(size_t size)
{
	t_heap *heap = g_heap_anchor;
	t_heap_group group = get_group(size);
	printf("Group: %d\n", group);
	t_block *block;
	while (heap)
	{
		if (heap->group == group)
		{
			printf("Heap found! Adredd: %p, Size: %ld, free: %ld\n",heap , heap->total_size, heap->free_size);
			// printf("adress heap %p\n", heap);

			block = (t_block *)HEAP_SHIFT(heap);
			while (block != NULL && block != (t_block*)0x1 && block != (t_block*)0xaaaaaaaaaaaaaaaa)
			{
				// printf("freed: %d, size: %ld nescessary: %ld\n", block->freed == TRUE,block->data_size,size + sizeof(t_block));
				printf("block adress in search: %p %p\n", block, (void *)block->data_size);
				if (block->freed && block->data_size >= size + sizeof(t_block))
				{
					printf("Block found %p\n", block);
					return (cut_block_from_heap(heap, block, size));
				}
				block = block->next;
			}
		}
		heap = heap->next;
	}
	printf("No heap found\n");
	return (NULL);
}