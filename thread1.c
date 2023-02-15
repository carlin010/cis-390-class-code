#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function();
int count = 0;

int main()
{
    pthread_t a_thread, b_thread;
    pthread_create(&a_thread, NULL, thread_function, NULL);
    pthread_create(&a_thread, NULL, thread_function, NULL);

    pthread_join(a_thread, NULL);
    pthread_join(b_thread, NULL);
    printf("%d\n",count);
    return 0;
}

void *thread_function()
{
    for (int i = 0; i < 1000000; i++) {
        // lock
        count++;
        // unlock 
    }
}