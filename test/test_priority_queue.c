#include <stdio.h>
#include <stdlib.h>

#include "../include/trait_queue.h"
#include "../include/priority_queue.h"

const char TEST_STR[] = "This_is_a_string_for_test";

struct st {
	int i;
	char s[];
};

int cmp(const void *lhs, const void *rhs)
{
	const struct st *_lhs = lhs;
	const struct st *_rhs = rhs;

	return (_lhs->i < _rhs->i) ? 1 : 0;
}

int main(void)
{
	printf(">>> Testing priority queue:\n");
	struct priority_queue_t *pq = make_priority_queue(16, cmp);
	struct trait_queue_t *_pq = (struct trait_queue_t *)pq;
	for (int i = 0; i < 20; ++i) {
		struct st *new = malloc(sizeof(*new) + (size_t)i + 2);
		new->i = 20 - i;
		sprintf(new->s, "%.*s", i + 1, TEST_STR);

		// Need to manually free if full
		if (!_pq->push(_pq, new))
			free(new);
	}
	for (int i = 0; i < 20; ++i) {
		struct st *curr = _pq->front(_pq);
		if (curr == NULL)
			printf("Priority queue is empty!\n");
		else
			printf("%s\n", curr->s);

		// Need to manually free before popping
		free(curr);
		_pq->pop(_pq);
	}
	destroy_priority_queue(pq);
	printf("<<< Completed testing priority queue.\n");

	return 0;
}

