/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:54:01 by jterrazz          #+#    #+#             */
/*   Updated: 2024/09/13 16:30:05 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*get_last_block(t_block *block)
{
	while (block->next)
		block = block->next;
	return (block);
}

void	find_available_block(size_t size, t_heap **res_heap, t_block **res_block)
{
	t_heap			*heap;
	t_block			*block;
	t_heap_group	group;

	heap = g_heap_anchor;
	group = get_heap_group_from_block_size(size);
	while (heap)
	{
		block = (t_block *)HEAP_SHIFT(heap);
		while (heap->group == group && block)
		{
			if (block->freed && (block->data_size >= size + sizeof(t_block)))
			{
				*res_heap = heap;
				*res_block = block;
				return ;
			}
			block = block->next;
		}
		heap = heap->next;
	}
	*res_heap = NULL;
	*res_block = NULL;
}
