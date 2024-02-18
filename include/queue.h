/**
 * Simple circular queue template.
 *
 * 2023 @megakite.
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "./trait_queue.h"

struct queue_t {
	/**
	 * impl trait Queue.
	 */
	struct trait_queue_t _impl;

	/**
	 * Local variables.
	 */
	size_t _capacity;
	size_t _front;
	size_t _back;
	void *_data[];
};

struct queue_t *make_queue(const size_t cap);
void destroy_queue(struct queue_t* q);

#endif//_QUEUE_H_
