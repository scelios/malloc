#include "../malloc.h"


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_str;
	char	*src_str;

	dst_str = (char *)dst;
	src_str = (char *)src;
	if (dst == src)
		return (dst);
	while (n--)
		*dst_str++ = *src_str++;
	return (dst);
}
