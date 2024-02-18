/**
 * Simple circular queue implementation.
 *
 * 2023 @megakite.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/queue.h"

static bool q_full(const void *self)
{
	const struct queue_t *_self = self;
	
	return _self->_front == (_self->_back + 1) % _self->_capacity;
}

static bool q_empty(const void *self)
{
	const struct queue_t *_self = self;

	return _self->_front == _self->_back;
}

static bool q_push(void *self, void *el)
{
	struct queue_t *_self = self;

	if (q_full(_self))
		return false;

	_self->_data[_self->_back] = el;
	_self->_back = (_self->_back + 1) % _self->_capacity;

	return true;
}

static bool q_pop(void *self)
{
	struct queue_t *_self = self;

	if (q_empty(_self))
		return false;
	
	_self->_data[_self->_front] = NULL;
	_self->_front = (_self->_front + 1) % _self->_capacity;
	
	return true;
}

static void *q_front(const void *self)
{
	const struct queue_t *_self = self;

	if (q_empty(_self))
		return NULL;
	
	return _self->_data[_self->_front];
}

static void *q_map(void *self, void *(*f)(void *el))
{
	struct queue_t *_self = self;

	size_t i = _self->_front;
	while (i != _self->_back) {
		_self->_data[i] = f(_self->_data[i]);
		i = (i + 1) % _self->_capacity;
	}

	return self;
}

struct queue_t *make_queue(const size_t cap)
{
	struct queue_t *new = calloc(1,
			sizeof(*new) + (cap + 1) * sizeof(uintptr_t));

	new->_impl.empty = q_empty;
	new->_impl.full = q_full;
	new->_impl.push = q_push;
	new->_impl.pop = q_pop;
	new->_impl.front = q_front;
	new->_impl.map = q_map;

	new->_front = 0;
	new->_back = 0;
	new->_capacity = cap + 1;

	return new;
}

void destroy_queue(struct queue_t *q)
{
	for (size_t i = 0; i < q->_capacity; ++i) {
		free(q->_data[i]);
	}
	free(q);
	q = NULL;
}
