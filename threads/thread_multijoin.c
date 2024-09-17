#include <pthread.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"

static pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

static int totThreads = 0, numLive = 0, numUnjoined = 0;

enum tstate
{
	TS_ALIVE,
	TS_TERMINATED,
	TS_JOINED
};

static struct
{
	pthread_t tid;
	enum tstate state;
	int sleepTime;
} *thread;

static void *threadFunc(void *arg)
{
	int idx = *((int *)arg);
	int s;
	sleep(thread[idx].sleepTime);
	printf("Thread %d terminating\n", idx);

	s = pthread_mutex_lock(&threadMutex);
	if (s != 0)
		errExitEN(s, "pthread_mutex_lock");

	numUnjoined++;
	thread[idx].state = TS_TERMINATED;

	s = pthread_mutex_unlock(&threadMutex);
	if (s != 0)
		errExitEN(s, "pthread_mutex_unlock");
	s = pthread_cond_signal(&threadDied);
	if (s != 0)
		errExitEN(s, "pthread_cond_signal");
	return;
}

int main(int argc, char const *argv[])
{
	int s, idx;
	return 0;
}
