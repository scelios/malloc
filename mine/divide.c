#include "malloc.h"

void divideBlock(size_t size,t_heap *heap, t_block *block)
{
	t_block *newBlock;
	if (block->data_size - size > sizeof(t_block) + 16) // + 16 to avoid fragmentation
	{
		newBlock = BLOCK_SHIFT(block) + size;
		newBlock->data_size = block->data_size - size - sizeof(t_block);
		newBlock->freed = TRUE;
		newBlock->next = block->next;
		newBlock->prev = block;
		if (block->next)
			block->next->prev = newBlock;
		
		block->data_size = size;
		block->next = newBlock;
	}
	block->freed = FALSE;
	heap->free_size -= block->data_size + sizeof(t_block);
	heap->block_count++;
}