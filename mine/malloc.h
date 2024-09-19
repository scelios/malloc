#ifndef MALLOC_H
# define MALLOC_H

# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>

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

typedef enum	e_detail_event {
	MALLOC,
	CALLOC,
	FREE,
	REALLOC,
	REALLOCF,
	HEAP_CREATE,
	HEAP_DELETE
}				t_detail_event;

typedef enum	e_env {
	ENV_STACK_LOGGING = 1 << 0,
	ENV_FULL_LOGGING = 1 << 1,
	ENV_SCRIBBLE = 1 << 2
}				t_env;

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

/*
** A block stores data for each malloc call
*/

typedef struct	s_block {
	struct s_block	*prev;
	struct s_block	*next;
	size_t			data_size;
	t_bool			freed;
}				t_block;

/*
** Library methods
*/

void			*malloc(size_t size);
void			*calloc(size_t count, size_t size);
void			*realloc(void *ptr, size_t size);
void			*reallocf(void *ptr, size_t size);
void			free(void *ptr);
void			show_alloc_mem();
void			show_alloc_mem_hex(void);

void	*ft_memset(void *b, int c, size_t len);
void	*start_malloc(size_t size);
t_block *create_heap(size_t size);
t_heap *last_heap(t_heap *heap);
t_block	*find_block(size_t size);
t_block *cut_block_from_heap(t_heap *heap, t_block *block, size_t size);
t_heap_group get_group(size_t size);
size_t get_heap_size_from_block_size(size_t size);

#endif