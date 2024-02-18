#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"

const char TEST_STR[] = "This_is_a_string_for_test";

struct st {
	char c;
	char s[];
};

int main(void)
{
	printf(">>> Testing queue:\n");
	struct queue_t *q = make_queue(16);
	struct trait_queue_t *_q = (struct trait_queue_t *)q;
	for (int i = 0; i < 20; ++i) {
		struct st *new = malloc(sizeof(*new) + (size_t)i + 2);
		sprintf(new->s, "%.*s", i + 1, TEST_STR);

		// Need to manually free if full
		if (!_q->push(_q, new))
			free(new);
	}
	for (int i = 0; i < 20; ++i) {
		struct st *curr = _q->front(_q);
		if (curr == NULL)
			printf("Queue is empty!\n");
		else
			printf("%s\n", curr->s);

		// Need to manually free before popping
		free(curr);
		_q->pop(_q);
	}
	destroy_queue(q);
	printf("<<< Completed testing queue.\n");

	return 0;
}

