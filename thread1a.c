#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function();
pthread_mutex_t mutex;
int count = 0;

int main()
{
    pthread_t a_thread, b_thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&a_thread, NULL, thread_function, NULL);
    pthread_create(&b_thread, NULL, thread_function, NULL);

    pthread_join(a_thread, NULL);
    pthread_join(b_thread, NULL);

    pthread_mutex_destroy(&mutex);
    printf("%d\n",count);
    return 0;
}

void *thread_function()
{
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}