#ifndef MALLOC_H
# define MALLOC_H

#include "./printf/ft_printf.h"
# include <fcntl.h>
# include <pthread.h>

# include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
// # include <unistd.h>

# define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

/*
** For a pagesize of 4096 bytes
**
** TINY  - block < 128 bytes  - heap 16 KB
** SMALL - block < 1024 bytes - heap 128 KB
** LARGE - block > 1024 bytes
*/

# define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
# define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (32 * getpagesize())
# define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

typedef enum	e_bool {
	FALSE,
	TRUE
}				t_bool;

typedef enum	e_heap_group {
	TINY,
	SMALL,
	LARGE
}				t_heap_group;

typedef enum	e_stack_event {
	ALLOCATE,
	DEALLOCATE
}				t_stack_event;

typedef struct	s_heap {
	struct s_heap	*prev;
	struct s_heap	*next;
	t_heap_group	group;
	size_t			total_size;
	size_t			free_size;
	size_t			block_count;
}				t_heap;

extern pthread_mutex_t		g_ft_malloc_mutex;
extern t_heap				*g_heap_anchor;

typedef struct	s_block {
	struct s_block	*prev;
	struct s_block	*next;
	size_t			data_size;
	t_bool			freed;
}				t_block;


void			*malloc(size_t size);
void			*calloc(size_t count, size_t size);
void			*realloc(void *ptr, size_t size);
void			*reallocf(void *ptr, size_t size);
void			free(void *ptr);
void			show_alloc_mem();
void loga(void);
void checkPrevNext();
void	start_free(void *ptr);
void	*start_malloc(size_t size);
void*start_realloc(void *ptr, size_t size);




void	*ft_memset(void *b, int c, size_t len);
void	*start_malloc(size_t size);
void createHeap(size_t size,t_heap **heap, t_block **block);
t_heap *lastHeap(t_heap *heap);
void findBlock(size_t size,t_heap **heap, t_block **block);
void divideBlock(size_t size,t_heap *heap, t_block *block);

t_heap_group getGroup(size_t size);
size_t get_heap_size_from_block_size(size_t size);
void searchPtr(void *ptr, t_heap **heap, t_block **block);

void show_alloc_mem();

void			ft_bzero(void *s, size_t n);
void			ft_putstr(char const *s);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_itoa_base(size_t nb, char base, char length, t_bool prefix);
void			ft_itoa_fd(size_t nb, char base, int fd, t_bool prefix);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putchar_fd(char c, int fd);
#endif