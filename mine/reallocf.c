#include "malloc.h"

void*start_reallocf(void *ptr, size_t size)
{
	void *res;

	res = start_realloc(ptr, size);
	if (!res && (size > 0))
		start_free(ptr);
	return (res);
}

void*reallocf(void *ptr, size_t size)
{
	void *res;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	res = start_reallocf(ptr, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (res);
}
