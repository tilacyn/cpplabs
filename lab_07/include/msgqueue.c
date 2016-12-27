#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "wsqueue.h"
struct payload {
	struct list_node link;
	int data;
};
static struct payload *create_payload(int data){
	struct payload *payload = malloc(sizeof(struct payload));
	if (payload)
		payload->data = data;
	return payload;
}
static volatile int cont = 1;
void *consumer(void *data)
{
	struct wsqueue *queue = data;
	puts("start consume loop");
	while (cont || queue_size(&queue->squeue.queue)) {
		struct list_node *node;
		pthread_mutex_lock(&queue->squeue.mutex);
		while (cont && !queue_size(&queue->squeue.queue))
			pthread_cond_wait(&queue->cond, &queue->squeue.mutex);
		pthread_mutex_unlock(&queue->squeue.mutex);
		node = wsqueue_pop(queue);
		if (node) {
			struct payload *data = (struct payload *)node;
			printf("consumer got value %d\n", data->data);
			free(node);
		}
	}
	puts("finish consume loop");
	return NULL;
}
int main()
{
	struct wsqueue queue;
	pthread_t ths[2];
	int rc, data;
	wsqueue_init(&queue);
	pthread_create(ths + 1, NULL, consumer, &queue);
	rc = pthread_create(ths, NULL, consumer, &queue);
	if (rc) {
		wsqueue_finit(&queue);
		perror("main");
		exit(1);
	}
	while (!feof(stdin)) {
		rc = scanf("%d", &data);
		if (rc == 1) {
			struct payload *payload = create_payload(data);
			if (!payload) {
				perror("main");
				break;
			}
			wsqueue_push(&queue, (struct list_node *)payload);
		}
	}
	cont = 0;
	wsqueue_notify_all(&queue);
	pthread_join(ths[0], NULL);
	pthread_join(ths[1], NULL);
	wsqueue_finit(&queue);
	return 0;
}
