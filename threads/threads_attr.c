#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
static void *threadFunc(void *arg)
{
        char *s = (char *) arg;
        printf("%s", s);
        return (void *) strlen(s);
}
int main(int argc, char *argv[])
{
    
pthread_t thr;
pthread_attr_t attr;
int s;
s = pthread_attr_init(&attr);
if (s != 0)
	perror("pthread_attr_init");
	/* Assigns default values */
s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
if (s != 0)
	perror("pthread_attr_setdetachstate");
else
	printf("set detached state\n");
s = pthread_create(&thr, &attr, threadFunc, (void *) 1);
if (s != 0)
	perror("pthread_create");
else
	printf("thread crested\n");

s = pthread_attr_destroy(&attr);
if (s != 0)
	perror("pthread_attr_destroy");
}
