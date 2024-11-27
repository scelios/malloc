/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 12:11:36 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./test.h"

static void *run_test_thread() {
	void *ret = malloc(80);
	free(ret);
	pthread_exit(NULL);
	return ret;
}

int main(void) {
	// void *b = malloc(2);
	// void *t = malloc(1000);
	// void *a = malloc(20000);
	// show_alloc_mem();
	// free(t);
	// free(a);
	// free(b);
	// show_alloc_mem();
	char *ret[1000];
	for (int i = 0; i < 1000; i++)
	{
		ret[i] = malloc(80);
	}
	// show_alloc_mem();

	for (int i = 0; i < 1000; i++)
	{
		free(ret[i]);
	}
	// show_alloc_mem();

	pthread_t *thread = malloc(sizeof(pthread_t) * 100);

	run_test_malloc();
	// run_test_realloc();
	// run_test_mixed();

	int i = 0;
	while (i < 100) {
		if (pthread_create(thread + i, NULL, run_test_thread, NULL)) {
			printf("Error pthread");
			return 0;
		}
		if (pthread_join(thread[i], NULL)) {
			printf("error pthread join");
			return 0;
		}
		i++;
	}
	return 0;
}
