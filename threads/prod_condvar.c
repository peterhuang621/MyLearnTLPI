#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "../lib/tlpi_hdr.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int avail = 0;

static void *producer(void *arg)
{
	int cnt = atoi((char *)arg);
	for (int j = 0; j < cnt; j++)
	{
		sleep(1);
		int s = pthread_mutex_lock(&mtx);
		if (s != 0)
			errExitEN(s, "pthread_mutex_lock");
		avail++;
		s = pthread_mutex_unlock(&mtx);
		if (s != 0)
			errExitEN(s, "pthread_mutex_unlock");
		s = pthread_cond_signal(&cond);
		if (s != 0)
			errExitEN(s, "pthread_cond_signal");
	}
	return NULL;
}