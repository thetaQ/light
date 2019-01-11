#include "threadpool.h"
#include <stdio.h>
#include <unistd.h>

#define THREAD_NUM 8
#define WORKER_MAX 10

void * demo_process(void * arg)
{
	printf("worker %d is processed\n", (int)arg);
	return 0;
}


int main(int argc, char ** argv)
{
	threadpool_t * threadpool = threadpool_create(THREAD_NUM);

	int i = 0;
	for(i = 0; i < WORKER_MAX; i++)
	{
		/**
 		* put a worker into threadpool, it's id is i
 		*/
		threadpool_put(threadpool, demo_process, (void *)i);
	}

	sleep(2);
	threadpool_destroy(threadpool);
	return 0;
}
