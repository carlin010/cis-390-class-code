// Run with cc -D_REENTRANT thread1.c -lpthread

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// new thead library
#include <pthread.h>

// prototype of function called by thead
void *thread_function(void *arg);

// globally defined variable
char message[] = "Hello World";

int main()
{
    int res;
    pthread_t a_thread;
    void *thread_result;
    // start running the thread
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for thread to finish...\n");
    // wait for thread to finish execution (similar to wait)
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined, it returned %s\n", (char *)thread_result);
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    printf("thread_function is running. Argument was %s\n", (char *)arg);
    sleep(3);
    // write new source "bye" to destination mem
    strcpy(message, "Bye!");
    pthread_exit("Thank you for the CPU time");
}