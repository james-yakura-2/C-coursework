#include "priority_queue.h";
#include <stdio.h>;

int main()
{
	PRIORITY_QUEUE queue = priority_queue_init_default();
	printf("Adding 1\n");
	priority_queue_insert(queue, 1, 1);
	printf("Adding 2\n");
	priority_queue_insert(queue, 1, 2);
	printf("Adding 3\n");
	priority_queue_insert(queue, 2, 3);
	printf("Adding 4\n");
	priority_queue_insert(queue, 4, 4);
	printf("Adding 5\n");
	priority_queue_insert(queue, 3, 5);

	printf("Removal pattern should be 4, 5, 3, 1, 2.\n");

	while (priority_queue_is_empty(queue) == FALSE)
	{
		printf("%d ", priority_queue_front(queue, NULL));
		priority_queue_service(queue);
	}

	printf("Cleaning up.");
	priority_queue_destroy(queue);
}