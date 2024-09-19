#include "malloc.h"

t_heap *last_heap(t_heap *heap)
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

size_t			get_heap_size_from_block_size(size_t size)
{
	t_heap_group heap_group;

	heap_group = get_heap_group_from_block_size(size);
	if (heap_group == TINY)
		return ((size_t)TINY_HEAP_ALLOCATION_SIZE);
	else if (heap_group == SMALL)
		return ((size_t)SMALL_HEAP_ALLOCATION_SIZE);
	return (size + sizeof(t_heap) + sizeof(t_block));
}

static rlim_t	get_system_limit(void)
{
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return (-1);
	return (rpl.rlim_max);
}

t_block *create_heap(size_t size)
{
	size_t heap_size = get_heap_size_from_block_size(size);
	t_block *block;

	if (heap_size > get_system_limit())
		return (NULL);
	t_heap *heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	printf("Heap created, adress %p\n", heap);
	if (heap == MAP_FAILED)
		return (NULL);
	ft_memset(heap, 0, heap_size);

	heap->prev = last_heap(g_heap_anchor);
	if (!g_heap_anchor)
		g_heap_anchor = heap;
	if (heap->prev)
		heap->prev->next = heap;
	heap->next = NULL;
	heap->group = get_group(size);
	heap->total_size = heap_size;
	heap->free_size = heap_size - sizeof(t_heap);
	heap->block_count = 1;
	block = (t_block *)HEAP_SHIFT(heap);
	printf("Block created, adress %p\n", block);
	block->data_size = heap_size;
	block->next = NULL;
	block->prev = NULL;
	block->freed = FALSE;
	printf("Heap created! Adress: %p, Size: %ld, free: %ld\n",heap , heap->total_size, heap->free_size);
	return cut_block_from_heap(heap, block, size);
}