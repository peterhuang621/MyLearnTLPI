#include "../lib/get_num.h"
#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"
#include <pthread.h>

static int glob = 0;

static void* threadFunc(void* arg) {
	int loops = *((int*)arg);
	int loc, j;
	for (j = 0; j < loops; j++) {
		loc = glob;
		loc++;
		glob = loc;
		// glob++; not work on arm64-Ubuntu22.04-macOS based
	}
	return NULL;
}

int main(int argc, char const* argv[]) {
	pthread_t t1, t2;
	int loops, s;
	loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;

	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if (s != 0)errExitEN(s, "pthread_create");
	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if (s != 0)errExitEN(s, "pthread_create");

	s = pthread_join(t1, NULL);
	if (s != 0)errExitEN(s, "pthread_join");
	s = pthread_join(t2, NULL);
	if (s != 0)errExitEN(s, "pthread_join");

	printf("glob = %d\n", glob);
	exit(EXIT_SUCCESS);
	return 0;
}
