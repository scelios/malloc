#include "malloc.h"

void*start_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*res;

	total_size = size * count;
	if (!count || !size || (total_size / count != size))
		return (NULL);
	if ((res = start_malloc(total_size)))
		ft_bzero(res, total_size);
	return (res);
}

void*calloc(size_t count, size_t size)
{
	void *res;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	res = start_calloc(count, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (res);
}
