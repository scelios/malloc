#include "malloc.h"

static rlim_t	get_system_limit(void)
{
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return (-1);
	return (rpl.rlim_max);
}

void createHeap(size_t size,t_heap **heap, t_block **block)
{
	t_heap *newHeap;
	t_block *newBlock;
	size_t heapSize;
	t_heap_group group;

	printf("create Heap\n");
	group = getGroup(size);
	group = TINY;
	heapSize = get_heap_size_from_block_size(size);
	heapSize = 4096;
	//!
	if (get_system_limit() < heapSize)
	{
		heap = NULL;
		block = NULL;
		return ;
	}
	newHeap = (t_heap *)mmap(0, heapSize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (newHeap == MAP_FAILED)
	{
		//printf("Failed to create heap\n");
		heap = NULL;
		block = NULL;
		return ;
	}
	newHeap->group = group;
	newHeap->total_size = heapSize;
	newHeap->free_size = heapSize - sizeof(t_heap);
	newHeap->block_count = 1;
	newHeap->prev = lastHeap(g_heap_anchor);
	newHeap->next = NULL;
	if (g_heap_anchor)
		lastHeap(g_heap_anchor)->next = newHeap;
	else
		g_heap_anchor = newHeap;
	newBlock = HEAP_SHIFT(newHeap);
	newBlock->data_size = heapSize - sizeof(t_heap) - sizeof(t_block);
	newBlock->freed = TRUE;
	newBlock->next = NULL;
	newBlock->prev = NULL;
	*heap = newHeap;
	*block = newBlock;
	//printf("Size block %ld\n", newBlock->data_size);
	//printf("End create Heap %p %p %p\n", (void *)*heap,(void *)*block, BLOCK_SHIFT(*block));
}