/**
 * Simple priority queue implementation.
 * 
 * 2023 @megakite.
 */

#include <stdlib.h>
#include <string.h>

#include "../include/priority_queue.h"

static void pq_percolate_down(struct priority_queue_t *self, size_t start)
{
	void *t = self->_data[start];

	size_t i = start;
	while (i * 2 <= self->_size) {
		size_t child = i * 2;
		if (child != self->_size
		    && self->_cmp(self->_data[child + 1], self->_data[child]))
			++child;

		if (self->_cmp(self->_data[child], t))
			self->_data[i] = self->_data[child];
		else
			break;

		i = child;
	}
	self->_data[i] = t;
}

static void pq_percolate_up(struct priority_queue_t *self, size_t start)
{
	void *t = self->_data[start];

	size_t i = start;
	while (i > 1 && self->_cmp(t, self->_data[i / 2])) {
		self->_data[i] = self->_data[i / 2];
		i /= 2;
	}
	self->_data[i] = t;
}

static bool pq_empty(const void *self)
{
	const struct priority_queue_t *_self = self;

	return _self->_size == 0;
}

static bool pq_full(const void *self)
{
	const struct priority_queue_t *_self = self;

	return _self->_size == _self->_capacity;
}

static bool pq_push(void *self, void *el)
{
	struct priority_queue_t *_self = self;

	if (pq_full(self))
		return false;
	
	++_self->_size;
	_self->_data[_self->_size] = el;
	pq_percolate_up(_self, _self->_size);
	
	return true;
}

static bool pq_pop(void *self)
{
	struct priority_queue_t *_self = self;
	
	if (pq_empty(self))
		return false;

	_self->_data[1] = _self->_data[_self->_size];
	_self->_data[_self->_size] = NULL;

	--_self->_size;
	pq_percolate_down(_self, 1);

	return true;
}

static void *pq_front(const void *self)
{
	const struct priority_queue_t *_self = self;

	if (pq_empty(_self))
		return NULL;
	
	return _self->_data[1];
}

static void *pq_map(void *self, void *(*f)(void *el))
{
	struct priority_queue_t *_self = self;

	for (size_t i = 1; i <= _self->_size; ++i) {
		_self->_data[i] = f(_self->_data[i]);
	}

	return self;
}

struct priority_queue_t *make_priority_queue(
	size_t cap,
	int (*cmp)(const void *lhs, const void *rhs))
{
	struct priority_queue_t *new = calloc(1, 
			sizeof(*new) + (cap + 1) * sizeof(uintptr_t));
	
	new->_impl.empty = pq_empty;
	new->_impl.full = pq_full;
	new->_impl.push = pq_push;
	new->_impl.pop = pq_pop;
	new->_impl.front = pq_front;
	new->_impl.map = pq_map;

	new->_cmp = cmp;
	
	new->_capacity = cap;
	new->_size = 0;

	return new;
}

void destroy_priority_queue(struct priority_queue_t *pq)
{
	for (size_t i = 1; i <= pq->_capacity; ++i) {
		free(pq->_data[i]);
	}
	free(pq);
	pq = NULL;
}
