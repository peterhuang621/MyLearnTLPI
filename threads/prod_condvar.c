#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"

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

int main(int argc, char const *argv[])
{
	time_t t = time(NULL);
	int totRequired = 0;
	for (int i = 1; i < argc; i++)
	{
		totRequired += atoi(argv[i]);
		pthread_t tid;
		int s = pthread_create(&tid, NULL, producer, argv[i]);
		if (s != 0)
			errExitEN(s, "pthread_create");
	}

	int numConsumed = 0;
	bool done = false;

	for (;;)
	{
		int s = pthread_mutex_lock(&mtx);
		if (s != 0)
			errExitEN(s, "pthread_mutex_lock");
		while (avail == 0)
		{
			s = pthread_cond_wait(&cond, &mtx);
			if (s != 0)
				errExitEN(s, "pthread_cond_wait");
		}
		while (avail > 0)
		{
			numConsumed++;
			avail--;
			printf("T=%ld: numConsumed=%d\n", (long)(time(NULL) - t), numConsumed);
			done = numConsumed >= totRequired;
		}

		s = pthread_mutex_unlock(&mtx);
		if (s != 0)
			errExitEN(s, "pthread_mutex_unlock");
		if (done)
			break;
	}
	exit(EXIT_SUCCESS);
	return 0;
}
