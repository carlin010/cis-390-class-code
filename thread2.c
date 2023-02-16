#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_functionA(void *arg);
void *thread_functionB(void *arg);

int run_now = 0; // 0=main 1=threadA 2=threadB

int main()
{
    int res,i;
    pthread_t a_thread, b_thread;
    void *thread_resultA, *thread_resultB;
    res = pthread_create(&a_thread, NULL, thread_functionA, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&b_thread, NULL, thread_functionB, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("\n Monitor run_now id every second\n");
    for(i=0;i<50;i++)
    {
        printf("%d",run_now);
        run_now = 0;
        fflush(stdout);
        sleep(1);
    }


    res = pthread_join(a_thread, &thread_resultA);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(b_thread, &thread_resultB);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void *thread_functionA(void *arg)
{
    printf("I am thread B\n");
    for(;;) {
        run_now = 1;
        usleep(1000);
    }
}

void *thread_functionB(void *arg)
{
    printf("I am thread B\n");
    for(;;) {
        run_now = 2;
        usleep(1000);
    }
}