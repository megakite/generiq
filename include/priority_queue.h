/** 
 * Simple priority queue template.
 *
 * 2023 @megakite.
 */

#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <stdint.h>
#include <stddef.h>

#include "./trait_queue.h"

struct priority_queue_t {
	/**
	 * impl trait Queue.
	 */
	struct trait_queue_t _impl;
	
	/**
	 * Design-specific functions.
	 */
	void (*_percolate_up)(struct priority_queue_t *self, size_t start);
	void (*_percolate_down)(struct priority_queue_t *self, size_t start);
	int (*_cmp)(const void *lhs, const void *rhs);

	/**
	 * Local variables.
	 */
	size_t _capacity;
	size_t _size;
	void *_data[];
};

struct priority_queue_t *make_priority_queue(size_t cap,
		int (*cmp)(const void *lhs, const void *rhs));
void destroy_priority_queue(struct priority_queue_t *pq);

#endif//_PRIORITY_QUEUE_H_
