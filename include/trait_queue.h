/**
 * Queue trait (interface).
 * 
 * Common behaviors of a queue (or some more general containers i guess) that
 * are ready for polymorphism.
 *
 * 2023 @megakite
 */

#ifndef _TRAIT_QUEUE_H_
#define _TRAIT_QUEUE_H_

#include <stdbool.h>

struct trait_queue_t {
	/**
	 * Check if the queue is empty.
	 */
	bool (*empty)(const void *self);

	/**
	 * Check if the queue is full.
	 */
	bool (*full)(const void *self);

	/**
	 * Push an element into the back of the queue.
	 * If failed, return false; else, return true.
	 */
	bool (*push)(void *self, void *el);
	
	/**
	 * Pop the front element from the queue.
	 * If failed, return false; else, return true.
	 *
	 * Note: this function shall not take the responsibility of freeing
	 *       the popped element, since user might use the queue to contain
	 *       non-malloc-ed objects.
	 */
	bool (*pop)(void *self);
	
	/**
	 * Get the front element from the queue.
	 * If failed, return NULL; else, return the element.
	 */
	void *(*front)(const void *self);

	/**
	 * Ode to the paradigm of functional programming
	 * Behaves like q.map((el) => { ... }); in JavaScript.
	 * 
	 * It's definitely not supposed to be here though (would be better if
	 * in `trait_iterable` or sth like that.) Alas, this approach to mock
	 * polymorphism doesn't allow us to implement more than one trait at a
	 * time.
	 */
	void *(*map)(void *self, void *(*f)(void *el));
};

#endif//_TRAIT_QUEUE_H_
