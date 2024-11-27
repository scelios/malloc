#include "malloc.h"

t_heap *lastHeap(t_heap *heap)
{
	if (!heap)
		return (NULL);
	while (heap->next)
		heap = heap->next;
	return (heap);
}

t_heap_group	get_heap_group_from_block_size(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY);
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}

size_t	get_heap_size_from_block_size(size_t size)
{
	t_heap_group heap_group;

	heap_group = get_heap_group_from_block_size(size);
	if (heap_group == TINY)
		return ((size_t)TINY_HEAP_ALLOCATION_SIZE);
	else if (heap_group == SMALL)
		return ((size_t)SMALL_HEAP_ALLOCATION_SIZE);
	return (size + sizeof(t_heap) + sizeof(t_block));
}



t_heap_group getGroup(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY);
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}

void searchPtr(void *ptr, t_heap **heap, t_block **block)
{
	t_heap *tmpHeap;
	t_block *tmpBlock;

	tmpHeap = g_heap_anchor;
	while (tmpHeap)
	{
		tmpBlock = HEAP_SHIFT(tmpHeap);
		while (tmpBlock)
		{
			if (BLOCK_SHIFT(tmpBlock) == ptr)
			{
				*heap = tmpHeap;
				*block = tmpBlock;
				return ;
			}
			tmpBlock = tmpBlock->next;
		}
		tmpHeap = tmpHeap->next;
	}
	*heap = NULL;
	*block = NULL;
}